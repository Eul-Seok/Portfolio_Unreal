// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_AOE.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monster/Monster.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/MonsterStatusComponent.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "Manager/GameMgr.h"
#include "Manager/SkillManager.h"

ASkill_AOE::ASkill_AOE():
	m_SkillSphereRadius{}, m_StartLocationFactor{}, m_EndLocationFactor{}, m_SpawnStartLocation{}, m_SpawnEndLocation{}, m_arOutHit{},
	m_pOutHit{}, m_HitImpact{}, m_HitGroundImpact{}, m_HitSound{}
{
	m_SkillSphereRadius = 50.0f;
	m_StartLocationFactor = 10.0f;
	m_EndLocationFactor = 500.0f;
}

void ASkill_AOE::BeginPlay()
{
	Super::BeginPlay();
	FVector PlayerLocation = m_Player->GetActorLocation();
	FVector PlayerForwardVector = m_Player->GetActorForwardVector();
	m_SpawnStartLocation = PlayerLocation + PlayerForwardVector * m_StartLocationFactor;
	m_SpawnEndLocation = m_SpawnStartLocation + PlayerForwardVector * m_EndLocationFactor;
}

void ASkill_AOE::ApplySkillAffect()
{
	float fSkillStrikingPower{};
	float fPlayerStrikingPower{};
	UMonsterStatusComponent* MonsterStatusComponent = Cast<AMonster>((*m_pOutHit).GetActor())->F_GetMonsterStatusComponent();
	fSkillStrikingPower = fPlayerStrikingPower;
	float fMonsterDefensivePower = MonsterStatusComponent->F_GetDefensivePower();
	if (m_SkillData)
	{
		float fSkillAffectValue = m_SkillData->m_AffectValue;
		if (fSkillAffectValue > 0.0f)
		{
			fPlayerStrikingPower = m_Player->F_GetPlayerStatusComponent()->F_GetStrikingPower();
			uint8 nSkillLevel = m_Player->F_GetGameMgr()->F_GetSkillMgr()->F_GetSpawnSkillLevel();
			float fSkillIncrementValue = 0.1f;
			fSkillStrikingPower = fPlayerStrikingPower * (fSkillAffectValue + (fSkillIncrementValue * (float)(nSkillLevel - 1)));
		}
	}	
	float fFinalDamage = fSkillStrikingPower - fMonsterDefensivePower;
	if (fFinalDamage < 1)
	{
		fFinalDamage = 1;
	}
	Cast<AMonster>((*m_pOutHit).GetActor())->F_ApplyHitDamage(fFinalDamage, &(*m_pOutHit).ImpactNormal);
}

void ASkill_AOE::SpawnImpact()
{
	if (m_HitImpact)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_HitImpact, (*m_pOutHit).ImpactPoint);
	}
	if (m_HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_HitSound, (*m_pOutHit).ImpactPoint);
	}
}

void ASkill_AOE::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Super::PlayMontageNotifyBegin(NotifyName, BranchingPointNotifyPayload);
	TArray<TEnumAsByte<EObjectTypeQuery>> arObjectTypes{};
	TEnumAsByte<EObjectTypeQuery> Monster = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	arObjectTypes.Add(Monster);
	TArray<AActor*> arIgnoredActors{};
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), m_SpawnStartLocation, m_SpawnEndLocation, m_SkillSphereRadius, arObjectTypes, false, arIgnoredActors, EDrawDebugTrace::None, m_arOutHit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	for (uint8 i = 0; i < m_arOutHit.Num(); i++)
	{
		AActor* HitActor = m_arOutHit[i].GetActor();
		if (HitActor != nullptr && HitActor->IsA(AMonster::StaticClass()))
		{
			m_pOutHit = &m_arOutHit[i];
			ApplySkillAffect();
			SpawnImpact();
		}
	}
}

