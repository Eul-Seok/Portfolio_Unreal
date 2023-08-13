// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_PlayMontage.generated.h"

UCLASS(Blueprintable)
class TESTCPP1_API UBTTaskNode_PlayMontage : public UBTTaskNode
{
	GENERATED_BODY()
		
public:
	UBTTaskNode_PlayMontage();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;
	UFUNCTION()
	void CallAttackEnd();
protected:
	UAnimMontage* m_AnimDefaultAttack;
	class AMonsterAIController* m_AIController;
	bool bAttacking;
};