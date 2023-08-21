// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemData.h"
#include "QuestContent.generated.h"

class UQuestObjectiveItem;
class URewardSlot;

UCLASS()
class TESTCPP1_API UQuestContent : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestContent(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestName;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ObjectiveList;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestDescription;
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Box_QuestNotComplete;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Reject;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Box_QuestComplete;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Close;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Complete;
	
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* RewardItemList;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_RewardExp;

protected:
	UPROPERTY()
	TSubclassOf<UQuestObjectiveItem> W_QuestObjectiveItem;
	UPROPERTY()
	TSubclassOf<URewardSlot> W_RewardSlot;
	class AGameMgr* m_pGameMgr;
	class AQuest* m_Quest;

protected:
	virtual void NativeOnInitialized() override;

protected:
	void ClearQuestObjectiveList();
	bool CheckQuestComplete();
	void Reward();
	void UpdateRewardBox(AQuest* Quest);
	URewardSlot* CreateRewardItemSlot(FItemData* ItemData);

public:
	void F_SetQuestInfo(AQuest* Quest);
	UFUNCTION()
	void OnButtonRejectClicked();
	UFUNCTION()
	void OnButtonAcceptClicked();
	UFUNCTION()
	void OnButtonCancleClicked();
	UFUNCTION()
	void OnButtonCompleteClicked();
};
