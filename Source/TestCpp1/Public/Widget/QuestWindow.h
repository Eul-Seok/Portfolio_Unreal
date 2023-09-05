// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemData.h"
#include "QuestWindow.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

class UQuestObjectiveItem;
class UQuestLogEntry;
class URewardSlot;
class AQuest;

UCLASS()
class TESTCPP1_API UQuestWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestWindow(const FObjectInitializer& ObjectInitializer);

protected:
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
	TSubclassOf<UQuestObjectiveItem> W_QuestObjectiveItem;
	UPROPERTY()
	TSubclassOf<UQuestLogEntry> W_QuestLogEntry;
	UPROPERTY()
	TSubclassOf<URewardSlot> W_RewardSlot;
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class UQuestLog* m_QuestLog;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
protected:
	void ClearQuestList();
	void UpdateRewardBox(AQuest* Quest);
	URewardSlot* CreateRewardItemSlot(FItemData* ItemData);

public:
	UFUNCTION()
	void F_CallUpdateActiveQuestInfo();

public:
	FDele_Multi DELE_UpdateActiveQuest;
};
