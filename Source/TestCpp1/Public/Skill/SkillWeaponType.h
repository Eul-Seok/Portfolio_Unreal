// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillWeaponType.generated.h"
class TESTCPP1_API SkillWeaponType
{
public:
	SkillWeaponType();
	~SkillWeaponType();
};

UENUM(BlueprintType)
enum class ESkillWeaponType : uint8
{
	E_Default = 0	UMETA(DisplayName = Default),
	E_Common		UMETA(DisplayName = Common),
	E_Katana		UMETA(DisplayName = Katana),
	E_SkillWeaponType_Max	UMETA(DisplayName = SkillWeaponType_Max)
};
