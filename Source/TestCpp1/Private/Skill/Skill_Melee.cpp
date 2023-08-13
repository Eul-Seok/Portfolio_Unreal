// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill/Skill_Melee.h"
#include "Player/TestCpp1Character.h"
#include "Player/MyPlayerController.h"

ASkill_Melee::ASkill_Melee()
{
}

void ASkill_Melee::BeginPlay()
{
	Super::BeginPlay();
	UAnimInstance* AnimInstance = m_Player->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ASkill_Melee::PlayMontageNotifyBegin);
		CompleteDelegate.BindUObject(this, &ASkill_Melee::FunctionToExecuteOnAnimationEnd);
		BlendOutDelegate.BindUObject(this, &ASkill_Melee::FunctionToExecuteOnAnimationBlendOut);
	}
	AnimInstance->Montage_Play(m_AnimMontage, 1.0f, EMontagePlayReturnType::MontageLength);
	AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimMontage);
	AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, m_AnimMontage);
	m_Player->F_SetbPlayingMontage(true);
	if (m_SkillData->m_CastTime == 0.0f)
	{
		AnimInstance->Montage_JumpToSection("CastEnd", m_AnimMontage);
	}
}

void ASkill_Melee::F_CastSkill()
{
	Super::F_CastSkill();
	UAnimInstance* AnimInstance = m_Player->GetMesh()->GetAnimInstance();
	if (m_SkillData->m_CastTime > 0.0f)
	{
		AnimInstance->Montage_JumpToSection("CastEnd", m_AnimMontage);
	}
}


void ASkill_Melee::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	UAnimInstance* AnimInstance = m_Player->GetMesh()->GetAnimInstance();
	AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ASkill_Melee::PlayMontageNotifyBegin);
}

void ASkill_Melee::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	m_Player->F_SetbPlayingMontage(false);
	Destroy();
}

void ASkill_Melee::FunctionToExecuteOnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	if (bInterrupted)
	{
		m_PlayerController->DELE_InterruptCasting.ExecuteIfBound();
	}
}
