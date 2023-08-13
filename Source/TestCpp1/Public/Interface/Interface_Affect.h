// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Affect/OperatorType.h"
#include "Interface_Affect.generated.h"

class ATestCpp1Character;
UINTERFACE(MinimalAPI)
class UInterface_Affect : public UInterface
{
	GENERATED_BODY()
};


class TESTCPP1_API IInterface_Affect
{
	GENERATED_BODY()

public:
	virtual bool F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator) = 0;
	virtual void F_ResetApply(ACharacter* Character) = 0;
};
