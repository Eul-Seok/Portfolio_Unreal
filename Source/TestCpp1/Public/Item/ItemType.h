// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

class TESTCPP1_API ItemType
{
public:
	ItemType();
	~ItemType();
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	E_Default = 0	UMETA(DisplayName = Default),
	E_Equipment	UMETA(DisplayName = Equipment),
	E_Consumption 		UMETA(DisplayName = Consumption),
	E_Quest		UMETA(DisplayName = Quest),
	E_ItemType_Max		UMETA(DisplayName = ItemType_Max)
};
