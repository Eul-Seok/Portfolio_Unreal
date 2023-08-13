// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OperatorType.generated.h"

class TESTCPP1_API OperatorType
{
public:
	OperatorType();
	~OperatorType();
};

UENUM(BlueprintType)
enum class EOperatorType : uint8
{
	E_Default		UMETA(DisplayName = Default),
	E_Plus			UMETA(DisplayName = Plus),
	E_Minus			UMETA(DisplayName = Minus),
	E_Multiply		UMETA(DisplayName = Multiply),
	E_Divide		UMETA(DisplayName = Divide),
	E_OperatorMax	UMETA(DisplayName = OperatorMax)
};

