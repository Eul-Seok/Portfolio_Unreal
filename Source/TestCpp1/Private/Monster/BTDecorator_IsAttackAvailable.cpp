// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTDecorator_IsAttackAvailable.h"
#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsAttackAvailable::UBTDecorator_IsAttackAvailable()
{
	NodeName = TEXT("IsAttackAvailable");
}

bool UBTDecorator_IsAttackAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	bool bResult{};
	AMonster* ControllingMonster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingMonster)
		return false;

	float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AMonsterAIController::Key_Distance);

	if (Distance >= 450.0f && Distance < 700.0f)
	{
		bResult = true;
	}
	else if (Distance >= 250.0f && Distance < 450.0f)
	{
		bResult = true;
	}
	else if (Distance > 0.0f && Distance < 250.0f)
	{
		bResult = true;
	}
	return bResult;
}
