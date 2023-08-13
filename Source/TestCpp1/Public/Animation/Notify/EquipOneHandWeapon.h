// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EquipOneHandWeapon.generated.h"

UCLASS()
class TESTCPP1_API UEquipOneHandWeapon : public UAnimNotify
{
	GENERATED_BODY()

public:
	UEquipOneHandWeapon();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	void AddWeaponDamage(ATestCpp1Character* Player);
	void UpdateApplyBuff(ATestCpp1Character* Player);
};
