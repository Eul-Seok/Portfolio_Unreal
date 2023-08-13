// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Quest/QuestObjectiveData.h"
#include "QuestSingleObjective.generated.h"

UCLASS()
class TESTCPP1_API UQuestSingleObjective : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestSingleObjective(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_IsComplete;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Description;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_AchievementCount;

protected:
	FQuestObjectiveData* m_ObjectiveData;

protected:
	void SetQuestInfoText();

public:
	void F_SetObjectiveData(FQuestObjectiveData* ObjectiveData);

};
