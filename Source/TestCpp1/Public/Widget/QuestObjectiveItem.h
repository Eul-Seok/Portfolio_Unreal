// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Quest/QuestObjectiveData.h"
#include "QuestObjectiveItem.generated.h"

UCLASS()
class TESTCPP1_API UQuestObjectiveItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UQuestObjectiveItem(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckBox_Complete;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Description;

protected:

public:
	void F_SetQuestObjectiveInfo(FQuestObjectiveData* pObjectiveData);
};
