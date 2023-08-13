// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsAttackAvailable.generated.h"

UCLASS()
class TESTCPP1_API UBTDecorator_IsAttackAvailable : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsAttackAvailable();	

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
