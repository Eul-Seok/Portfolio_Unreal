// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/PlayerStatusComponent.h"
#include "Manager/GameMgr.h"
#include "Player/TestCpp1Character.h"
#include "Skill/Skill_Buff.h"

UPlayerStatusComponent::UPlayerStatusComponent() :
	m_pGameMgr{}, m_Player{}, m_fExpMax{}, m_fExpCurrent{}, m_fExpNormalized{}, m_pPlayerLevelUpDataTable{}, m_ParticleLevelUp{},
	m_nStrength{}, m_nAgility{}, m_nConstitution{}, m_nIntelligence{}, m_fIncrementPower{}, m_fIncrementStatusBar{}, m_nIncrementStatusPoint{}, m_nIncrementSkillPoint{},
	m_nStatusPoint{}, m_nSkillPoint{}

{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PLAYERLEVELUPDATA(TEXT("/Game/Player/DT_PlayerLevelUpData"));
	if (DT_PLAYERLEVELUPDATA.Succeeded())
	{
		{ m_pPlayerLevelUpDataTable = DT_PLAYERLEVELUPDATA.Object; }
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PARTICLE_LEVELUP(TEXT("/Game/Player/P_LevelUp"));
	if (PARTICLE_LEVELUP.Succeeded())
	{
		m_ParticleLevelUp = PARTICLE_LEVELUP.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find m_ParticleLevelUp"));
	}

	Init();
}

void UPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(GetOwner());
	F_SetRegenTimer();
}

void UPlayerStatusComponent::HealthRegenTick()
{
	Super::HealthRegenTick();
	if (m_fHealthCurrent < m_fHealthMax)
	{
		float NewHealth = m_fHealthCurrent + (m_fHealthMax * 0.1f);
		m_fHealthCurrent = UKismetMathLibrary::FClamp(NewHealth, 0.0f, m_fHealthMax);
		m_fHealthNormalized = UKismetMathLibrary::NormalizeToRange(m_fHealthCurrent, 0.0f, m_fHealthMax);
		DELE_RequestUpdateStatusBar.Broadcast();
	}
}

void UPlayerStatusComponent::ManaRegenTick()
{
	Super::ManaRegenTick();
	if (m_fManaCurrent < m_fManaMax)
	{
		float NewMana = m_fManaCurrent + (m_fManaMax * 0.1f);
		m_fManaCurrent = UKismetMathLibrary::FClamp(NewMana, 0.0f, m_fManaMax);
		m_fManaNormalized = UKismetMathLibrary::NormalizeToRange(m_fManaCurrent, 0.0f, m_fManaMax);
		DELE_RequestUpdateStatusBar.Broadcast();
	}
}

void UPlayerStatusComponent::Init()
{
	m_nLevel = 1;
	m_fExpMax = 100.0f;
	
	m_nStrength = 5.0f;
	m_nAgility = 5.0f;
	m_nConstitution = 5.0f;
	m_nIntelligence = 5.0f;

	m_nStatusPoint = 5;
	m_nSkillPoint = 10;

	m_fIncrementPower = 3.0f;
	m_fIncrementStatusBar = 50.0f;
	m_nIncrementSkillPoint = 2;
	m_nIncrementStatusPoint = 5;
	
	m_fStrikingPower = m_nStrength * m_fIncrementPower;
	m_fDefensivePower = m_nAgility * m_fIncrementPower;
	m_fHealthMax = m_nConstitution * m_fIncrementStatusBar;
	m_fManaMax = m_nIntelligence * m_fIncrementStatusBar;
	m_fHealthCurrent = m_fHealthMax;
	m_fManaCurrent = m_fManaMax;
}

void UPlayerStatusComponent::LevelUp()
{
	m_nLevel++;
	FName RowName = FName(FString::FromInt(m_nLevel));
	m_fExpMax = m_pPlayerLevelUpDataTable->FindRow<FPlayerLevelUpData>(RowName, "")->m_Exp;
	LevelUpReward();
	if (m_ParticleLevelUp != nullptr)
	{
		FVector ParticleLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_ParticleLevelUp, ParticleLocation, FRotator::ZeroRotator, ((FVector)((2.0f))));
	}
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundLevelUp);
}

void UPlayerStatusComponent::LevelUpReward()
{
	m_nSkillPoint += m_nIncrementSkillPoint;
	m_nStatusPoint += m_nIncrementStatusPoint;
	F_CompleteRecovery();
	DELE_LevelUp.Broadcast();
}

void UPlayerStatusComponent::UpdateApplyBuff(const ATestCpp1Character* Player)
{
	TArray<AActor*> arAttachedActor{};
	Player->GetAttachedActors(arAttachedActor);
	for (uint8 i = 0; i < arAttachedActor.Num(); i++)
	{
		ASkill_Buff* BuffSkill = Cast<ASkill_Buff>(arAttachedActor[i]);
		if (BuffSkill)
		{
			BuffSkill->F_UpdateApplyBuff();
		}
	}
}

void UPlayerStatusComponent::F_StatusUpApply(EPlayerStatus eStatus)
{
	if (eStatus == EPlayerStatus::E_Strength)
	{
		m_nStrength++;
		m_fStrikingPower += m_fIncrementPower;
		DELE_RequestUpdatePower.ExecuteIfBound();
	}
	else if (eStatus == EPlayerStatus::E_Agility)
	{
		m_nAgility++;
		m_fDefensivePower += m_fIncrementPower;
		DELE_RequestUpdatePower.ExecuteIfBound();
	}
	else if (eStatus == EPlayerStatus::E_Constitution)
	{
		m_nConstitution++;
		m_fHealthMax += m_fIncrementStatusBar;
		m_fHealthNormalized = UKismetMathLibrary::NormalizeToRange(m_fHealthCurrent, 0.0f, m_fHealthMax);
		DELE_RequestUpdateStatusBar.Broadcast();
	}
	else if (eStatus == EPlayerStatus::E_Intelligence)
	{
		m_nIntelligence++;
		m_fManaMax += m_fIncrementStatusBar;
		m_fManaNormalized = UKismetMathLibrary::NormalizeToRange(m_fManaCurrent, 0.0f, m_fManaMax);
		DELE_RequestUpdateStatusBar.Broadcast();
	}
	UpdateApplyBuff(m_Player);
	m_nStatusPoint--;

}

void UPlayerStatusComponent::F_SetRegenTimer()
{
	GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &UPlayerStatusComponent::HealthRegenTick, 10.0f, true);
	GetWorld()->GetTimerManager().SetTimer(ManaRegenTimerHandle, this, &UPlayerStatusComponent::ManaRegenTick, 10.0f, true);
}

void UPlayerStatusComponent::F_CompleteRecovery()
{
	m_fHealthCurrent = m_fHealthMax;
	m_fManaCurrent = m_fManaMax;
	m_fHealthNormalized = 1.0f;
	m_fManaNormalized = 1.0f;
}

void UPlayerStatusComponent::F_AddHealth(float fValue)
{
	Super::F_AddHealth(fValue);
	DELE_RequestUpdateStatusBar.Broadcast();
}

void UPlayerStatusComponent::F_AddMana(float fValue)
{
	Super::F_AddMana(fValue);
	DELE_RequestUpdateStatusBar.Broadcast();
}

void UPlayerStatusComponent::F_ReduceHealth(float fValue)
{
	Super::F_ReduceHealth(fValue);
	DELE_RequestUpdateStatusBar.Broadcast();
}

void UPlayerStatusComponent::F_ReduceMana(float fValue)
{
	Super::F_ReduceMana(fValue);
	DELE_RequestUpdateStatusBar.Broadcast();
}

void UPlayerStatusComponent::F_ChangeAttackStrikingPower(float fValue, EOperatorType eOperator)
{
	Super::F_ChangeAttackStrikingPower(fValue, eOperator);
	DELE_RequestUpdatePower.ExecuteIfBound();
}

void UPlayerStatusComponent::F_ChangeBuffAppliedStrikingPower(float fValue, EOperatorType eOperator)
{
	Super::F_ChangeBuffAppliedStrikingPower(fValue, eOperator);
	DELE_RequestUpdatePower.ExecuteIfBound();
}

void UPlayerStatusComponent::F_ChangeBuffAppliedDefensivePower(float fValue, EOperatorType eOperator)
{
	Super::F_ChangeBuffAppliedDefensivePower(fValue, eOperator);
	DELE_RequestUpdatePower.ExecuteIfBound();
}

void UPlayerStatusComponent::F_ResetAttackStrikingPower()
{
	Super::F_ResetAttackStrikingPower();
	DELE_RequestUpdatePower.ExecuteIfBound();
}

void UPlayerStatusComponent::F_ResetBuffAppliedStrikingPower()
{
	Super::F_ResetBuffAppliedStrikingPower();
	DELE_RequestUpdatePower.ExecuteIfBound();
}

void UPlayerStatusComponent::F_ResetBuffAppliedDefensivePower()
{
	Super::F_ResetBuffAppliedDefensivePower();
	DELE_RequestUpdatePower.ExecuteIfBound();
}


void UPlayerStatusComponent::F_AddExp(float fValue)
{
	float NewExp = m_fExpCurrent + fValue;
	m_fExpCurrent = UKismetMathLibrary::FClamp(NewExp, 0.0f, m_fExpMax);
	if (m_fExpMax <= NewExp)
	{
		float RemainingExp = NewExp - m_fExpMax;
		LevelUp();
		m_fExpCurrent = RemainingExp;
	}
	m_fExpNormalized = UKismetMathLibrary::NormalizeToRange(m_fExpCurrent, 0.0f, m_fExpMax);
	DELE_RequestUpdateStatusBar.Broadcast();
}

void UPlayerStatusComponent::F_SetSkillPoint(uint8 nNewSkillPoint)
{
	m_nSkillPoint = nNewSkillPoint;
}

void UPlayerStatusComponent::F_SetStrikingPower(float fNewStrikingPower)
{
	m_fStrikingPower = fNewStrikingPower;
}

void UPlayerStatusComponent::F_SetDefensivePower(float fNewDefensivePower)
{
	m_fDefensivePower = fNewDefensivePower;
}

void UPlayerStatusComponent::F_SetStrength(uint8 nNewStrength)
{
	m_nStrength = nNewStrength;
}

void UPlayerStatusComponent::F_SetAgility(uint8 nNewAgility)
{
	m_nAgility = nNewAgility;
}

void UPlayerStatusComponent::F_SetConstitution(uint8 nNewConstitution)
{
	m_nConstitution = nNewConstitution;
}

void UPlayerStatusComponent::F_SetIntelligence(uint8 nNewIntelligence)
{
	m_nIntelligence = nNewIntelligence;
}

void UPlayerStatusComponent::F_SetStatusPoint(uint8 nNewStatusPoint)
{
	m_nStatusPoint = nNewStatusPoint;	
}
