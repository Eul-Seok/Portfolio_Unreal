// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemData.h"
#include "Skill/SkillData.h"
#include "Widget/SlotType.h"
#include "QuickSlotData.generated.h"

USTRUCT(BlueprintType)
struct FQuickSlotData
{
	GENERATED_USTRUCT_BODY()

public:
	FQuickSlotData();

public:
	FItemData* m_pQuickSlotItemData;
	FSkillData* m_pQuickSlotSkillData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESlotType m_ePairSlotType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 m_nPairSlotIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bRegistration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bCooldown;
	FTimerHandle* m_pCooldownTimerHandle;
};
