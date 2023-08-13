

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterSkill_Base.h"
#include "RampageSkill_Buff.generated.h"

UCLASS()
class TESTCPP1_API ARampageSkill_Buff : public AMonsterSkill_Base
{
	GENERATED_BODY()
	
public:
	ARampageSkill_Buff();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float m_fBuffDuration;
	class IInterface_Affect* m_Interface_Affect;

public:
	virtual void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted) override;
	virtual void ResetEffect() override;
	virtual void ActivateEffect() override;
};
