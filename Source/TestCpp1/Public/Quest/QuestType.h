// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class TESTCPP1_API QuestType
{
public:
	QuestType();
	~QuestType();
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	E_Default = 0			UMETA(DisplayName = Default),
	E_Location			UMETA(DisplayName = Location),
	E_Interact				UMETA(DisplayName = Interact),
	E_Collect 			UMETA(DisplayName = Collect),
	E_Kill			UMETA(DisplayName = Kill),
	E_QuestTypeMax	UMETA(DisplayName = Max)
};