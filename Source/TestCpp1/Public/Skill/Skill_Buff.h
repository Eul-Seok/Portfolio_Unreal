// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Melee.h"
#include "Interface/Interface_Affect.h"
#include "Skill_Buff.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS()
class TESTCPP1_API ASkill_Buff : public ASkill_Melee
{
	GENERATED_BODY()

public:
	ASkill_Buff();

protected:
	FTimerHandle m_BuffTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fBuffLifeSpan;
	IInterface_Affect* m_Interface_Affect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_SkillParticle;
	UPROPERTY()
	UParticleSystemComponent* m_SpawnedSkillParticle;

protected:
	virtual void BeginPlay() override;

protected:
	void ClearDuplicates();
	void ApplyBuff();
	void ClearBuff();
	EOperatorType GetReverseOperator(EOperatorType Operator);

public:
	virtual void F_CastSkill() override;
	void F_UpdateApplyBuff();

public:
	FTimerHandle* F_GetBuffTimerHandle();

public:
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) override;
	void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted) override;

public:
	FDele_Multi DELE_BuffRemoved;
};
