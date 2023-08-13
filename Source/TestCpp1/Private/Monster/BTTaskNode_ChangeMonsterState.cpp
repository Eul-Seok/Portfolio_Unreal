// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_ChangeMonsterState.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTaskNode_ChangeMonsterState::UBTTaskNode_ChangeMonsterState():
	m_eMonsterState{}
{
}

EBTNodeResult::Type UBTTaskNode_ChangeMonsterState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Initialize faild!"));
		return EBTNodeResult::Failed;
	}
	Controller->GetBlackboardComponent()->SetValueAsEnum(AMonsterAIController::Key_MosterState, (uint8)m_eMonsterState);
	if (m_eMonsterState == EMonsterState::E_Chase)
	{
		Monster->F_RotateToFacePlayer();
	}
	return EBTNodeResult::Succeeded;
}
 