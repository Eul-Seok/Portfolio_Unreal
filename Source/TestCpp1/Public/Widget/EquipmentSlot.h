// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Widget/Slot_Base.h"
#include "EquipmentSlot.generated.h"

UCLASS()
class TESTCPP1_API UEquipmentSlot : public USlot_Base
{
	GENERATED_BODY()

public:
	UEquipmentSlot(const FObjectInitializer& ObjectInitializer);
};

// 구현 안함.