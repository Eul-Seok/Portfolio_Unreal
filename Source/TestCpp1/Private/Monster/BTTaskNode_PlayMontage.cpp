// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_PlayMontage.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"
#include "Monster/MonsterState.h"

UBTTaskNode_PlayMontage::UBTTaskNode_PlayMontage():
	m_AnimDefaultAttack{}, m_AIController{}, bAttacking{}
{
	bNotifyTick = true;
	bAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	m_AIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Cast<AMonster>(m_AIController->GetPawn());
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Initialize faild!"));
		return EBTNodeResult::Failed;
	}

	Monster->F_Attack();
	bAttacking = true;
	Monster->DELE_AttackEnd.AddUFunction(this, FName("CallAttackEnd"));

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_PlayMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);
	if (!bAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTaskNode_PlayMontage::CallAttackEnd()
{
	bAttacking = false;
	AMonster* Monster = Cast<AMonster>(m_AIController->GetPawn());
	Monster->DELE_AttackEnd.Clear();
}



