// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindRandomLocation.generated.h"

UCLASS(Blueprintable)
class TESTCPP1_API UBTTaskNode_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FindRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
};
