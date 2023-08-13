// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Interface/Interface_Affect.h"
#include "Affect/AffectType.h"
#include "AttackSetting.generated.h"

UCLASS()
class TESTCPP1_API UAttackSetting : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	float CalculatefFinalAffectValue(float AffectValue, uint8 SkillLevel);
	void GetInterfaceAffect(AActor* Pawn);
	void ApplyAffect(AActor* Pawn, EOperatorType Operator);
	void ResetAffect(AActor* Pawn);
	void SetAttackAvailable(AActor* Pawn, bool IsAttackAvailable);
	FAttackData* FindAttackData();

protected:
	UPROPERTY()
	class ATestCpp1Character* m_Player;
	UPROPERTY()
	class AMonster* m_Monster;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAffectType m_eAffectType {EAffectType::E_AttackStrikingPowerChange};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fAffectValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle m_AttackDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackHand m_AttackHand;
	uint8 m_SkillLevel;
	IInterface_Affect* m_Interface_Affect;
};
