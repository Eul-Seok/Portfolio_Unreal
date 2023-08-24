
#include "Skill/Skill_Base.h"
#include "Player/TestCpp1Character.h"
#include "Player/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/GameMgr.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/CastBar.h"

ASkill_Base::ASkill_Base():
	m_pCaster{}, m_pTarget{}, m_pGameMgr{}, m_Player{}, m_PlayerController{}, m_pSkillDataTable{}, m_SkillData{},
	m_SkillRowName{}, m_CastTime{}, m_AnimMontage{}, m_DestroyTimerHandle{}
{
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 10.0f;
}

void ASkill_Base::BeginPlay()
{
	Super::BeginPlay();
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	m_PlayerController = Cast<AMyPlayerController>(m_Player->GetController());
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_SkillData = m_pSkillDataTable->FindRow<FSkillData>(m_SkillRowName, "");
	AttachToComponent(m_pCaster->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("Hand_R"));
	F_BeginCating();
}

void ASkill_Base::DestroySkill()
{
	Destroy();
}

void ASkill_Base::ApplySkillAffect()
{
}

void ASkill_Base::F_BeginCating()
{
	m_Player->F_SetbCasting(true);
	if (m_SkillData->m_CastTime > 0)
	{
		UCastBar* CastBar = m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayCastBar(this);
		CastBar->DELE_CompletedCast.BindUFunction(this, FName("F_CastSkill"));
	}
	else
	{
		F_CastSkill();
	}
}

void ASkill_Base::F_CastSkill()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	m_Player->F_GetPlayerStatusComponent()->F_ReduceMana(m_SkillData->m_Cost);
	m_Player->F_SetbCasting(false);
	DELE_CastSuccess.ExecuteIfBound();
}

void ASkill_Base::F_InterruptedCast()
{
	m_Player->StopAnimMontage();
	m_Player->F_SetbCasting(false);
	m_Player->F_SetbPlayingMontage(false);
	DELE_CastInterrupted.ExecuteIfBound();
	GetWorld()->GetTimerManager().SetTimer(m_DestroyTimerHandle, this, &ASkill_Base::DestroySkill, 1.0f, false);
}

void ASkill_Base::F_ActivateEffect()
{
}

void ASkill_Base::F_SetCaster(ACharacter* Caster)
{
	m_pCaster = Caster;
}

void ASkill_Base::F_SetTarget(ACharacter* Target)
{
	m_pTarget = Target;
}