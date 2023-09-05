// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Affect/AffectType.h"
#include "MonsterSkill_Base.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS()
class TESTCPP1_API AMonsterSkill_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonsterSkill_Base();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class AMonster* m_Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> m_SkillDecal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_SkillParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffectType m_eAffectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fAffectValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bStunSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fStunDuration;
	UPROPERTY()
	class UParticleSystemComponent* m_SpawnedSkillParticle;
	UPROPERTY()
	class ASkillDecal* m_SpawnedSkillDecal;

	FTimerHandle m_ParticleTimerHandle;
	FOnMontageEnded CompleteDelegate;

protected:
	UFUNCTION()
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	virtual void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted);
	virtual void ResetEffect();
	virtual void ActivateEffect();
	virtual ASkillDecal* SpawnDecal();

public:
	virtual void F_ApplySkillDamge(AActor* Player);
	
public:
	FDele_Multi DELE_SkillMontageEnd;

};