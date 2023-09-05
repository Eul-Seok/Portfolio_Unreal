// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterSkill_Base.h"
#include "RampageSkill_StoneThrow.generated.h"

class AProjectileObject;

UCLASS()
class TESTCPP1_API ARampageSkill_StoneThrow : public AMonsterSkill_Base
{
	GENERATED_BODY()

public:
	ARampageSkill_StoneThrow();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fCastTime;
	bool m_bHasStone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectileObject> m_ProjectileClass;
	UPROPERTY()
	AProjectileObject* m_ProjectileObject;

protected:
	virtual void BeginPlay() override;
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) override;
	virtual void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted) override;
	void CreateStone();
	void Throw();
	void CalculatePlayerGroundLocation(const FVector& TargetLocation, FVector& TargetGroundLocation);
	virtual ASkillDecal* SpawnDecal() override;
};
