// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackType.generated.h"

class TESTCPP1_API AttackType
{
public:
	AttackType();
	~AttackType();
};


UENUM(BlueprintType)
enum class EAttackType : uint8
{
	E_Default = 0	UMETA(DisplayName = Default),
	E_SmallStrike	UMETA(DisplayName = SmallStrike),
	E_MiddleStrike 		UMETA(DisplayName = MiddleStrike),
	E_LargeStrike		UMETA(DisplayName = LargeStrike),
	E_AttackTypeMax		UMETA(DisplayName = AttackTypeMax)
};

UENUM(BlueprintType)
enum class EAttackHand : uint8
{
	E_Default = 0	UMETA(DisplayName = Default),
	E_RightHand	UMETA(DisplayName = RightHand),
	E_LeftHand 		UMETA(DisplayName = LeftHand),
	E_AttackHandMax		UMETA(DisplayName = AttackHandMax)
};