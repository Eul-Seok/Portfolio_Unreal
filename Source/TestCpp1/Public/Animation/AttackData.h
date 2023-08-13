// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Animation/AttackType.h"
#include "AttackData.generated.h"

USTRUCT(BlueprintType)
struct FAttackData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FAttackData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType m_AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsKnockBack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsStun;
};

