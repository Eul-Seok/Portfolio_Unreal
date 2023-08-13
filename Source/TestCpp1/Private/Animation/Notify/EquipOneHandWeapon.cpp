// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EquipOneHandWeapon.h"
#include "Player/TestCpp1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Item/Weapon_Base.h"
#include "Manager/GameMgr.h"
#include "Manager/AffectManager.h"
#include "Skill/Skill_Buff.h"
#include "ActorComponent/PlayerStatusComponent.h"

UEquipOneHandWeapon::UEquipOneHandWeapon() :Super()
{
}

void UEquipOneHandWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp && MeshComp->GetOwner())
	{
		ATestCpp1Character* Player = Cast<ATestCpp1Character>(MeshComp->GetOwner());
		if (Player&& Player->F_GetWeapon())
		{
			Player->F_GetWeapon()->AttachToComponent(Player->F_GetSceneWeaponRigth(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
			Player->F_SetbOneHandWeaponEquippeed(true);
			AddWeaponDamage(Player);
			UpdateApplyBuff(Player);
		}
	}
}

void UEquipOneHandWeapon::AddWeaponDamage(ATestCpp1Character* Player)
{
	float fWeaponDamage = Player->F_GetWeapon()->F_GetWeaponDamage();
	float fNewStrikingPower = Player->F_GetPlayerStatusComponent()->F_GetStrikingPower() + fWeaponDamage;
	UPlayerStatusComponent* PlayerStatusComponent = Player->F_GetPlayerStatusComponent();
	PlayerStatusComponent->F_SetStrikingPower(fNewStrikingPower);
	PlayerStatusComponent->DELE_RequestUpdatePower.ExecuteIfBound();
}

void UEquipOneHandWeapon::UpdateApplyBuff(ATestCpp1Character* Player)
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
