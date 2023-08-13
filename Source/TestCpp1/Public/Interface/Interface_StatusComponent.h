// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Affect/OperatorType.h"
#include "Interface_StatusComponent.generated.h"

UINTERFACE(MinimalAPI)
class UInterface_StatusComponent : public UInterface
{
	GENERATED_BODY()
};


class TESTCPP1_API IInterface_StatusComponent
{
	GENERATED_BODY()

protected:
	virtual void HealthRegenTick() = 0;
	virtual void ManaRegenTick() = 0;
	virtual float CalculateChangeValue(float fStatus, float fValue, EOperatorType eOperator) = 0;

public:
	virtual void F_AddHealth(float fValue) = 0;
	virtual void F_AddMana(float fValue) = 0;
	virtual void F_ReduceHealth(float fValue) = 0;
	virtual void F_ReduceMana(float fValue) = 0;
	virtual void F_ChangeAttackStrikingPower(float fValue, EOperatorType eOperator) = 0;
	virtual void F_ChangeBuffAppliedStrikingPower(float fValue, EOperatorType eOperator) = 0;
	virtual void F_ChangeBuffAppliedDefensivePower(float fValue, EOperatorType eOperator) = 0;
	virtual void F_ResetAttackStrikingPower() = 0;
	virtual void F_ResetBuffAppliedStrikingPower() = 0;
	virtual void F_ResetBuffAppliedDefensivePower() = 0;
	virtual void F_ClearRegenTimer() = 0;
	virtual float F_GetStrikingPower() = 0;
	virtual float F_GetDefensivePower() = 0;
};
