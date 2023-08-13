// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_FindRandomLocation.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_FindRandomLocation::UBTTaskNode_FindRandomLocation():
	Radius{}
{
}

EBTNodeResult::Type UBTTaskNode_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Initialize faild!"));
		return EBTNodeResult::Failed;
	}
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NevSystem faild!"));
		return EBTNodeResult::Failed;
	}
	FVector const Origin = Monster->GetActorLocation();
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomReachablePointInRadius(Origin, Radius, NextPatrol, nullptr))
	{
		Blackboard->SetValueAsVector(AMonsterAIController::Key_PatrolLocation, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	Blackboard->SetValueAsVector(AMonsterAIController::Key_PatrolLocation, Origin);
	return EBTNodeResult::Succeeded;
}
