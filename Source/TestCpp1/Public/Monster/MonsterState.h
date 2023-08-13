// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class TESTCPP1_API MonsterState
{
public:
	MonsterState();
	~MonsterState();
};

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	E_Idle = 0			UMETA(DisplayName = Idle),
	E_Patrol			UMETA(DisplayName = Patrol),
	E_Chase				UMETA(DisplayName = Chase),
	E_Attack 			UMETA(DisplayName = Attack),
	E_Skill			UMETA(DisplayName = Skill),
	E_KnockBack			UMETA(DisplayName = KnockBack),
	E_MonsterStateMax	UMETA(DisplayName = Max)
};