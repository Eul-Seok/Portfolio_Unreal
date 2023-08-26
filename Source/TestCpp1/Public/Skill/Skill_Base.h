// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill/SkillData.h"
#include "Skill_Base.generated.h"

DECLARE_DELEGATE(FDele_Single);

UCLASS()
class TESTCPP1_API ASkill_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkill_Base();

protected:
	UPROPERTY()
	ACharacter* m_pCaster;
	UPROPERTY()
	ACharacter* m_pTarget;
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class ATestCpp1Character* m_Player;
	UPROPERTY()
	class AMyPlayerController* m_PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* m_pSkillDataTable;
	FSkillData* m_SkillData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_SkillRowName;
	float m_CastTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimMontage;
	FTimerHandle m_DestroyTimerHandle;

	FOnMontageEnded CompleteDelegate;
	FOnMontageEnded BlendOutDelegate;

protected:
	virtual void BeginPlay() override;

protected:
	void DestroySkill();
	virtual void ApplySkillAffect();

public:	
	void F_BeginCating();
	UFUNCTION()
	virtual void F_CastSkill();
	void F_InterruptedCast();
	virtual void F_ActivateEffect();

public:
	void F_SetCaster(ACharacter* Caster);
	void F_SetTarget(ACharacter* Target);

public:
	FORCEINLINE FName* F_GetSkillRowName() { return &m_SkillRowName; }
	FORCEINLINE float F_GetCastTime() { return m_SkillData->m_CastTime; }
	FORCEINLINE UDataTable* F_GetSkillDataTable() { return m_pSkillDataTable; }
	FORCEINLINE FSkillData* F_GetSkillData() { return m_SkillData; }

public:
	FDele_Single DELE_CastSuccess;
	FDele_Single DELE_CastInterrupted;
};
