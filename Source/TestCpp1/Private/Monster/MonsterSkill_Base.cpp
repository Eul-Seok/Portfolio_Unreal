
#include "Monster/MonsterSkill_Base.h"
#include "Item/Weapon_Base.h"
#include "Monster/Monster.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/PlayerStatusComponent.h"

AMonsterSkill_Base::AMonsterSkill_Base()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMonsterSkill_Base::BeginPlay()
{
	Super::BeginPlay();
	m_Monster = Cast<AMonster>(GetOwner());
	m_Monster->F_RotateToFacePlayer();
	UAnimInstance* AnimInstance = m_Monster->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AMonsterSkill_Base::PlayMontageNotifyBegin);
		CompleteDelegate.BindUObject(this, &AMonsterSkill_Base::FunctionToExecuteOnAnimationEnd);
	}
}

void AMonsterSkill_Base::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	UAnimInstance* AnimInstance = m_Monster->GetMesh()->GetAnimInstance();
	AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AMonsterSkill_Base::PlayMontageNotifyBegin);
}

void AMonsterSkill_Base::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	CompleteDelegate.Unbind();
}

void AMonsterSkill_Base::ResetEffect()
{
}

void AMonsterSkill_Base::ActivateEffect()
{
}

ASkillDecal* AMonsterSkill_Base::SpawnDecal()
{
	return nullptr;
}

void AMonsterSkill_Base::F_ApplySkillDamge(AActor* Player)
{
	AWeapon_Base* MonsterWeapon = Cast<AMonster>(GetOwner())->F_GetLeftWeapon();
	if (MonsterWeapon != nullptr)
	{
		ATestCpp1Character* HitPlayer = Cast<ATestCpp1Character>(Player);
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(MonsterWeapon->GetRootComponent());
		HitPlayer->F_Hit(Component);
		if (m_bStunSkill && HitPlayer->F_GetPlayerStatusComponent()->F_GetHealthCurrent() > 0.0f)
		{
			HitPlayer->F_PlayStun(m_fStunDuration);
		}
	}
}
