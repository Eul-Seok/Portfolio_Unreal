// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerLevelUpData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLevelUpData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FPlayerLevelUpData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_Exp;
};
