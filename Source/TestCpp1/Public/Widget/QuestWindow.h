// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemData.h"
#include "QuestWindow.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS()
class TESTCPP1_API UQuestWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestWindow(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(meta = (BindWidget))
	class UTitleBar* W_TitleBar;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* StoryQuestList;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* SideQuestList;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestName;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ObjectiveList;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestDescription;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* RewardBox;
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* RewardItemList;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_RewardExp;


protected:
	UPROPERTY()
	TSubclassOf<class UQuestObjectiveItem> W_QuestObjectiveItem;
	UPROPERTY()
	TSubclassOf<class UQuestLogEntry> W_QuestLogEntry;
	UPROPERTY()
	TSubclassOf<class URewardSlot> W_RewardSlot;
	class AGameMgr* m_pGameMgr;
	class UQuestLog* m_QuestLog;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
protected:
	void ClearQuestList();
	void UpdateRewardBox(class AQuest* Quest);
	URewardSlot* CreateRewardItemSlot(FItemData* ItemData);

public:
	UFUNCTION()
	void F_CallUpdateActiveQuestInfo();

public:
	FDele_Multi DELE_UpdateActiveQuest;
};
