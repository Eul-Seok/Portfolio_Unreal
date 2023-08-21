
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_UseMonsterSkill.generated.h"

UENUM(BlueprintType)
enum class EMonsterSkill : uint8
{
	E_StoneThrow = 0			UMETA(DisplayName = StoneThrow),
	E_Smash			UMETA(DisplayName = Smash),
	E_Buff				UMETA(DisplayName = Buff),
	E_MonsterSkilleMax	UMETA(DisplayName = Max)
};

class AMonsterSkill_Base;

UCLASS(Blueprintable)
class TESTCPP1_API UBTTaskNode_UseMonsterSkill : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_UseMonsterSkill();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;
	UFUNCTION()
	void CallSkillMontageEnd();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonsterSkill m_eMonsterSkill;
	UPROPERTY()
	AMonsterSkill_Base* m_SpawnMonsterSkill;
	bool bAttacking;

};