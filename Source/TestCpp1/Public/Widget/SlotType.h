// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotType.generated.h"

class TESTCPP1_API SlotType
{
public:
	SlotType();
	~SlotType();
};

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	E_Default		UMETA(DisplayName = DefaultSlot),
	E_InventorySlot	UMETA(DisplayName = InventorySlot),
	E_SkillSlot		UMETA(DisplayName = SkillSlot),
	E_QuickSlot		UMETA(DisplayName = QuickSlot),
	E_EquipmentSlot UMETA(DisplayName = EquipmentSlot),
	E_RewardSlot	UMETA(DisplayName = RewardSlot),
	E_SlotTypeMax	UMETA(DisplayName = SlotTypeMax)
};
