// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_UseMonsterSkill.h"
#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterSkill_Base.h"
#include "ActorComponent/MonsterSkillsComponent.h"

UBTTaskNode_UseMonsterSkill::UBTTaskNode_UseMonsterSkill()
{
    bNotifyTick = true;
    bAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_UseMonsterSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    AMonsterAIController* AIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
    AMonster* Monster = Cast<AMonster>(AIController->GetPawn());
    TArray<TSubclassOf<AMonsterSkill_Base>>* arMonsterSkill = Monster->F_GetMonsterSkillsComponent()->F_GetMonsterSkillList();
    if ((*arMonsterSkill).IsValidIndex((uint8)m_eMonsterSkill))
    {
        TSubclassOf<AMonsterSkill_Base> MonsterSkill = (*arMonsterSkill)[(uint8)m_eMonsterSkill];
        UWorld* World = GetWorld();
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = Monster;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);
        m_SpawnMonsterSkill = World->SpawnActor<AMonsterSkill_Base>(MonsterSkill, SpawnTransform, SpawnParameters);
        bAttacking = true;
        m_SpawnMonsterSkill->DELE_SkillMontageEnd.AddUFunction(this, FName("CallSkillMontageEnd"));
        return EBTNodeResult::InProgress;
    }
    return EBTNodeResult::Failed;
}

void UBTTaskNode_UseMonsterSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);
    if (!bAttacking)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

void UBTTaskNode_UseMonsterSkill::CallSkillMontageEnd()
{
    bAttacking = false;
    m_SpawnMonsterSkill->DELE_SkillMontageEnd.Clear();
}
