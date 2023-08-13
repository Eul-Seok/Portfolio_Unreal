// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Quest/QuestType.h"
#include "QuestObjectiveData.generated.h"

USTRUCT(BlueprintType)
struct FQuestObjectiveData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FQuestObjectiveData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType m_QuestType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bComplete;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> m_Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 m_nNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 m_nAchievementCount;
};

