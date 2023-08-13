// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Monster/MonsterState.h"
#include "BTTaskNode_ChangeMonsterState.generated.h"

UCLASS(Blueprintable)
class TESTCPP1_API UBTTaskNode_ChangeMonsterState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_ChangeMonsterState();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonsterState m_eMonsterState;
	
};
