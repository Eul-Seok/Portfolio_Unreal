
#pragma once

#include "CoreMinimal.h"
#include "Affect/Affect_base.h"
#include "Affect_BuffAppliedDefensivePowerChange.generated.h"

UCLASS()
class TESTCPP1_API UAffect_BuffAppliedDefensivePowerChange : public UAffect_base
{
	GENERATED_BODY()
public:
	UAffect_BuffAppliedDefensivePowerChange();

public:
	virtual bool F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator) override;
	virtual void F_ResetApply(ACharacter* Character) override;
};
