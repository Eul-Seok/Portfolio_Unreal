// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestObjectives.generated.h"

class UQuestSingleObjective;

UCLASS()
class TESTCPP1_API UQuestObjectives : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestObjectives(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ObjectiveList;

protected:
	UPROPERTY()
	TSubclassOf<UQuestSingleObjective> W_QuestSingleObjective;
	class AGameMgr* m_pGameMgr;
	class UQuestLog* m_QuestLog;

protected:
	virtual void NativeOnInitialized() override;
public:
	void F_UpdateObjectives();
};
