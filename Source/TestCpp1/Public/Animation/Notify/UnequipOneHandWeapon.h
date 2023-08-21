// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "UnequipOneHandWeapon.generated.h"

class ATestCpp1Character;

UCLASS()
class TESTCPP1_API UUnequipOneHandWeapon : public UAnimNotify
{
	GENERATED_BODY()
public:
	UUnequipOneHandWeapon();

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	void MinusWeaponDamage(ATestCpp1Character* Player);
	void UpdateApplyBuff(const ATestCpp1Character* Player);
};
