// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Affect/Affect_base.h"
#include "Affect_Default.generated.h"

/**
 * 
 */
UCLASS()
class TESTCPP1_API UAffect_Default : public UAffect_base
{
	GENERATED_BODY()
	
public:
	UAffect_Default();

public:
	bool F_Apply(ACharacter*, float fValue, EOperatorType eOperator);
};
