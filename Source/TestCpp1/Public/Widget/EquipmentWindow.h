// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWindow.generated.h"

UCLASS()
class TESTCPP1_API UEquipmentWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UEquipmentWindow(const FObjectInitializer& ObjectInitializer);

};

// 구현 안함.