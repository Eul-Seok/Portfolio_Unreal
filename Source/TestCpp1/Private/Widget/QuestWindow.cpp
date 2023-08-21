// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestWindow.h"
#include "Widget/QuestObjectiveItem.h"
#include "Widget/QuestLogEntry.h"
#include "Widget/TitleBar.h"
#include "Widget/RewardSlot.h"
#include "Components/VerticalBox.h"
#include "Components/WrapBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/InventoryManager.h"
#include "Quest/QuestLog.h"
#include "Quest/Quest.h"
#include "Item/Item.h"

UQuestWindow::UQuestWindow(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuestWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_QuestLog = m_pGameMgr->F_GetQuestLogComponent();
	W_QuestObjectiveItem = m_pGameMgr->F_GetWidgetMgr()->F_GetBPQuestObjectiveItem();
	W_QuestLogEntry = m_pGameMgr->F_GetWidgetMgr()->F_GetBPQuestLogEntry();
	W_RewardSlot = m_pGameMgr->F_GetWidgetMgr()->F_GetBPRewardSlot();
	DELE_UpdateActiveQuest.AddUFunction(this, FName("F_CallUpdateActiveQuestInfo"));
	
	W_TitleBar->F_GetTitleTextBlock()->SetText(FText::FromString(FString::Printf(TEXT("퀘스트창"))));
	RewardBox->SetVisibility(ESlateVisibility::Hidden);
}

void UQuestWindow::NativeConstruct()
{
	Super::NativeConstruct();
	
	ClearQuestList();
	TArray<AQuest*>* arQuest = m_QuestLog->F_GetarQuest();
	for (uint8 i = 0; i < (*arQuest).Num(); i++)
	{
		/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("arQuest : %s"), *(*arQuest)[0]->GetName()));*/
		UQuestLogEntry* NewQuestLogEntry = CreateWidget<UQuestLogEntry>(this, W_QuestLogEntry);
		NewQuestLogEntry->F_SetQuestInfo((*arQuest)[i]);
		if ((*arQuest)[i]->F_GetbStoryQuest())
		{
			StoryQuestList->AddChild(NewQuestLogEntry);
		}
		else
		{
			SideQuestList->AddChild(NewQuestLogEntry);
		}
	}
}

void UQuestWindow::ClearQuestList()
{
	StoryQuestList->ClearChildren();
	SideQuestList->ClearChildren();
}

void UQuestWindow::UpdateRewardBox(AQuest* Quest)
{
	RewardItemList->ClearChildren();
	UDataTable* ItemDataTable = m_pGameMgr->F_GetInventoryMgr()->F_GetItemDataTable();
	TArray<TSubclassOf<AItem>>* arRewardItem = Quest->F_GetarRewardItem();
	for (uint8 i = 0; i < arRewardItem->Num(); i++)
	{
		FName* NewItemName = (*arRewardItem)[i].GetDefaultObject()->F_GetRowName();
		FItemData* NewItemData = ItemDataTable->FindRow<FItemData>(*NewItemName, "");
		URewardSlot* NewRewardSlot = CreateRewardItemSlot(NewItemData);
		RewardItemList->AddChildToWrapBox(NewRewardSlot);
	}
	Text_RewardExp->SetText(FText::FromString(FString::Printf(TEXT("경험치 보상: %.0f"), Quest->F_GetRewardExp())));
}

URewardSlot* UQuestWindow::CreateRewardItemSlot(FItemData* ItemData)
{
	URewardSlot* pNewRewardSlot = CreateWidget<URewardSlot>(this, W_RewardSlot);
	pNewRewardSlot->F_SetItemData(ItemData);
	return pNewRewardSlot;
}

void UQuestWindow::F_CallUpdateActiveQuestInfo()
{
	ObjectiveList->ClearChildren();
	AQuest* ActiveQuest = m_QuestLog->F_GetActiveQuest();
	if (ActiveQuest)
	{
		Text_QuestName->SetText(*ActiveQuest->F_GetName());
		Text_QuestDescription->SetText(*ActiveQuest->F_GetDescription());
		TArray<FQuestObjectiveData>* arQuestObjectiveData = ActiveQuest->F_GetObjectiveData();
		for (uint8 i = 0; i < (*arQuestObjectiveData).Num(); i++)
		{
			UQuestObjectiveItem* NewObjectiveItem = CreateWidget<UQuestObjectiveItem>(this, W_QuestObjectiveItem);
			NewObjectiveItem->F_UpdateQuestObjectiveInfo(&(*arQuestObjectiveData)[i]);
			ObjectiveList->AddChild(NewObjectiveItem);
		}
		RewardBox->SetVisibility(ESlateVisibility::Visible);
		UpdateRewardBox(ActiveQuest);
	}
	else
	{
		Text_QuestName->SetText(FText::FromString(""));
		Text_QuestDescription->SetText(FText::FromString(""));
		RewardBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

