// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_Buff.h"
#include "Player/TestCpp1Character.h"
#include "Monster/Monster.h"
#include "Manager/GameMgr.h"
#include "Manager/AffectManager.h"
#include "Manager/WidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/TargetBar.h"
#include "Widget/BuffPanel.h"
#include "Widget/BuffIcon.h"
#include "Affect/Affect_base.h"
#include "Particles/ParticleSystemComponent.h"

ASkill_Buff::ASkill_Buff():
	m_BuffTimerHandle{}, m_fBuffLifeSpan{}, m_Interface_Affect{}, m_SkillParticle{}, m_SpawnedSkillParticle{}
{

}
void ASkill_Buff::BeginPlay()
{
	Super::BeginPlay();
	m_Interface_Affect = Cast<IInterface_Affect>(m_pGameMgr->F_GetAffectMgr()->F_GetAffect(m_SkillData->m_AffectType));
}

void ASkill_Buff::ClearDuplicates()
{
	TArray<AActor*> arAttachedActor{};
	if (!m_pTarget)
	{
		m_pCaster->GetAttachedActors(arAttachedActor);
	}
	else
	{
		m_pTarget->GetAttachedActors(arAttachedActor);
	}
	for (uint8 i = 0; i < arAttachedActor.Num(); i++)
	{
		if (arAttachedActor[i]->GetClass() == GetClass())
		{
			Cast<ASkill_Buff>(arAttachedActor[i])->ClearBuff();
		}
	}
}

void ASkill_Buff::ApplyBuff()
{
	if (!m_pTarget)
	{
		m_Interface_Affect->F_Apply(m_pCaster, m_SkillData->m_AffectValue, m_SkillData->m_AffectOperator);
		m_SpawnedSkillParticle = UGameplayStatics::SpawnEmitterAttached(m_SkillParticle, m_Player->GetMesh(), FName("pelvis"), FVector(ForceInit), FRotator::ZeroRotator, FVector((FVector)((8.0f))), EAttachLocation::SnapToTarget);
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetBuffPanel()->F_AddBuff(this);
	}
	else
	{
		m_Interface_Affect->F_Apply(m_pTarget, m_SkillData->m_AffectValue, m_SkillData->m_AffectOperator);
		m_SpawnedSkillParticle = UGameplayStatics::SpawnEmitterAttached(m_SkillParticle, Cast<AMonster>(m_pTarget)->GetMesh(), FName("pelvis"), FVector(ForceInit), FRotator::ZeroRotator, FVector((FVector)((8.0f))), EAttachLocation::SnapToTarget);
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetTargetBar()->F_UpdateBuffIcon();
	}
}

void ASkill_Buff::ClearBuff()
{
	if (!m_pTarget)
	{
		m_Interface_Affect->F_ResetApply(m_pCaster);
	}
	else
	{
		m_Interface_Affect->F_ResetApply(m_pTarget);
	}
	m_SpawnedSkillParticle->DestroyComponent();
	DELE_BuffRemoved.Broadcast();
	Destroy();
}

EOperatorType ASkill_Buff::GetReverseOperator(EOperatorType Operator)
{
	EOperatorType ReverseOperator{};
	if (Operator == EOperatorType::E_Plus)
	{
		ReverseOperator = EOperatorType::E_Minus;
	}
	if (Operator == EOperatorType::E_Minus)
	{
		ReverseOperator = EOperatorType::E_Plus;
	}
	if (Operator == EOperatorType::E_Multiply)
	{
		ReverseOperator = EOperatorType::E_Divide;
	}
	if (Operator == EOperatorType::E_Divide)
	{
		ReverseOperator = EOperatorType::E_Multiply;
	}
	return ReverseOperator;
}

void ASkill_Buff::F_CastSkill()
{
	Super::F_CastSkill();
}

void ASkill_Buff::F_UpdateApplyBuff()
{
	if (!m_pTarget)
	{
		m_Interface_Affect->F_Apply(m_pCaster, m_SkillData->m_AffectValue, m_SkillData->m_AffectOperator);
	}
	else
	{
		m_Interface_Affect->F_Apply(m_pTarget, m_SkillData->m_AffectValue, m_SkillData->m_AffectOperator);
	}
}

FTimerHandle* ASkill_Buff::F_GetBuffTimerHandle()
{
	return &m_BuffTimerHandle;
}

void ASkill_Buff::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Super::PlayMontageNotifyBegin(NotifyName, BranchingPointNotifyPayload);
	ClearDuplicates();
	if (!m_pTarget)
	{
		AttachToActor(m_pCaster, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	}
	else
	{
		AttachToActor(m_pTarget, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	}
	SetLifeSpan(m_fBuffLifeSpan + 10.0f);
	ApplyBuff();
	GetWorld()->GetTimerManager().SetTimer(m_BuffTimerHandle, this, &ASkill_Buff::ClearBuff, m_fBuffLifeSpan, false);
}

void ASkill_Buff::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	m_Player->F_SetbPlayingMontage(false);
}
