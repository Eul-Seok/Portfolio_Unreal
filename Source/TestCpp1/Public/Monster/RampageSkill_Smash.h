// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterSkill_Base.h"
#include "RampageSkill_Smash.generated.h"

UCLASS()
class TESTCPP1_API ARampageSkill_Smash : public AMonsterSkill_Base
{
	GENERATED_BODY()

public:
	ARampageSkill_Smash();

protected:
	FVector m_SpawnLocation;
	float m_SkillSphereRadius;

protected:
	virtual void BeginPlay() override;
	void CastComplete();
	virtual ASkillDecal* SpawnDecal() override;

protected:
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) override;
	virtual void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted) override;

public:
	virtual void F_ApplySkillDamge(AActor* Player) override;
	
	
};
