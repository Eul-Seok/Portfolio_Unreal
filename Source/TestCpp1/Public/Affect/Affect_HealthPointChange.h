// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Affect/Affect_base.h"
#include "Affect_HealthPointChange.generated.h"

UCLASS()
class TESTCPP1_API UAffect_HealthPointChange : public UAffect_base
{
	GENERATED_BODY()
public:
	UAffect_HealthPointChange();

public:
	virtual bool F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator) override;
};
