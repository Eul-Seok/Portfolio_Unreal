// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffectType.generated.h"

class TESTCPP1_API AffectType
{
public:
	AffectType();
	~AffectType();
};

UENUM(BlueprintType)
enum class EAffectType : uint8
{
	E_Default = 0						UMETA(DisplayName = Default),
	E_HealthPointChange					UMETA(DisplayName = HealthPointChange),
	E_ManaPointChange					UMETA(DisplayName = ManaPointChange),
	E_AttackStrikingPowerChange			UMETA(DisplayName = AttackStrikingPowerChange),
	E_BuffAppliedStrikingPowerChange	UMETA(DisplayName = BuffAppliedStrikingPowerChange),
	E_BuffAppliedDefensivePowerChange	UMETA(DisplayName = BuffAppliedDefensivePowerChange),
	E_Affect_Max						UMETA(DisplayName = Affect_Max)
};