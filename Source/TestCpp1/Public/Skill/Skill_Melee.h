// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Base.h"
#include "Skill_Melee.generated.h"

UCLASS()
class TESTCPP1_API ASkill_Melee : public ASkill_Base
{
	GENERATED_BODY()

public:
	ASkill_Melee();

protected:
	virtual void BeginPlay() override;

public:
	virtual void F_CastSkill() override;
	
public:
	UFUNCTION()
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	virtual void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted);
	void FunctionToExecuteOnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);

};
