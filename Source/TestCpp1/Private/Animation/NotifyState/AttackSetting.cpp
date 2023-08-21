// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/AttackSetting.h"
#include "Player/TestCpp1Character.h"
#include "Monster/Monster.h"
#include "Manager/GameMgr.h"
#include "Manager/SkillManager.h"
#include "Manager/AffectManager.h"
#include "Skill/Skill_Base.h"
#include "Engine/DataTable.h"
#include "Item/Weapon_Base.h"
#include "Affect/Affect_base.h"

void UAttackSetting::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp && MeshComp->GetOwner())
	{
		AActor* Pawn = MeshComp->GetOwner();
		if (Pawn->IsA(ATestCpp1Character::StaticClass()))
		{
			m_Player = Cast<ATestCpp1Character>(Pawn);
			m_SkillLevel = m_Player->F_GetGameMgr()->F_GetSkillMgr()->F_GetSpawnSkillLevel();
		}
		SetAttackAvailable(Pawn, true);
		if (m_fAffectValue != 0)
		{
			ApplyAffect(Pawn, EOperatorType::E_Multiply);
		}
	}
}

void UAttackSetting::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp && MeshComp->GetOwner())
	{
		AActor* Pawn = MeshComp->GetOwner();
		SetAttackAvailable(Pawn, false);
		if (m_fAffectValue != 0)
		{
			ResetAffect(Pawn);
		}
	}
}

float UAttackSetting::CalculatefFinalAffectValue(float AffectValue, uint8 SkillLevel)
{
	float fFinalAffectValue{};
	float fSkillIncrementValue = 0.1f;
	fFinalAffectValue = AffectValue + (fSkillIncrementValue * (float)(SkillLevel-1));
	return fFinalAffectValue;
}

void UAttackSetting::GetInterfaceAffect(const AActor* Pawn)
{
	if (Pawn->IsA(ATestCpp1Character::StaticClass()))
	{
		m_Interface_Affect = Cast<IInterface_Affect>(m_Player->F_GetGameMgr()->F_GetAffectMgr()->F_GetAffect(m_eAffectType));
	}
	else if (Pawn->IsA(AMonster::StaticClass()))
	{
		m_Interface_Affect = Cast<IInterface_Affect>(m_Monster->F_GetGameMgr()->F_GetAffectMgr()->F_GetAffect(m_eAffectType));
	}
}

void UAttackSetting::ApplyAffect(AActor* Pawn, EOperatorType Operator)
{
	float fFinalAffectValue{};
	fFinalAffectValue = m_fAffectValue;
	if (Pawn->IsA(ATestCpp1Character::StaticClass()))
	{
		fFinalAffectValue = CalculatefFinalAffectValue(m_fAffectValue, m_SkillLevel);
	}
	GetInterfaceAffect(Pawn);
	if(m_Interface_Affect)
	{
		m_Interface_Affect->F_Apply(Cast<ACharacter>(Pawn), fFinalAffectValue, Operator);
	}
}

void UAttackSetting::ResetAffect(AActor* Pawn)
{
	if(m_Interface_Affect)
	{
		m_Interface_Affect->F_ResetApply(Cast<ACharacter>(Pawn));
	}
}

void UAttackSetting::SetAttackAvailable(AActor* Pawn, bool IsAttackAvailable)
{
	if (Pawn->IsA(ATestCpp1Character::StaticClass()))
	{
		AWeapon_Base* Weapon = m_Player->F_GetRightHandWeapon();
		if (Weapon != nullptr)
		{
			m_Player->F_SetWeaponAttackAvailable(IsAttackAvailable);
		}
	}
	else if (Pawn->IsA(AMonster::StaticClass()))
	{
		m_Monster = Cast<AMonster>(Pawn);
		AWeapon_Base* LeftWeapon = m_Monster->F_GetLeftWeapon();
		AWeapon_Base* RightWeapon = m_Monster->F_GetRightWeapon();
		if (LeftWeapon != nullptr || RightWeapon !=nullptr)
		{
			FAttackData* AttackData = FindAttackData();
			if (m_AttackHand == EAttackHand::E_LeftHand)
			{
				LeftWeapon->F_SetbKnockBackAttack(AttackData->m_IsKnockBack);
				LeftWeapon->F_SetbStunAttack(AttackData->m_IsStun);
			}
			else
			{
				RightWeapon->F_SetbKnockBackAttack(AttackData->m_IsKnockBack);
				RightWeapon->F_SetbStunAttack(AttackData->m_IsStun);
			}
			m_Monster->F_SetWeaponAttackAvailable(m_AttackHand, IsAttackAvailable);
		}
	}
}

FAttackData* UAttackSetting::FindAttackData()
{
	return m_AttackDataTable.DataTable->FindRow<FAttackData>(m_AttackDataTable.RowName, "");
}
