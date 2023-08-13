// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTService_CheckDistance.h"
#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterState.h"
#include "ActorComponent/MonsterSkillsComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckDistance::UBTService_CheckDistance()
{
	NodeName = TEXT("CheckDistance");
	Interval = 1.0f;
	bCallTickOnSearchStart = true;
}

void UBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingMonster = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingMonster ==  nullptr)
		return;
	UWorld* World = ControllingMonster->GetWorld();
	if (World == nullptr)
		return;
	
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::Key_Player));
	float Distance = ControllingMonster->GetDistanceTo(Player);
	uint8 MonsterState = OwnerComp.GetBlackboardComponent()->GetValueAsEnum(AMonsterAIController::Key_MosterState);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AMonsterAIController::Key_Distance,Distance);
}
