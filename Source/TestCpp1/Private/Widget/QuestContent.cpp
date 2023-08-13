// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestContent.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Quest/Quest.h"
#include "Quest/QuestLog.h"
#include "Manager/GameMgr.h"
#include "Manager/InventoryManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/QuestObjectiveItem.h"
#include "Widget/QuestWindow.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/QuestObjectives.h"
#include "Widget/RewardSlot.h"
#include "NPC/NPC.h"
#include "Item/Item.h"

UQuestContent::UQuestContent(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuestContent::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	W_QuestObjectiveItem = m_pGameMgr->F_GetWidgetMgr()->F_GetBPQuestObjectiveItem();
	W_RewardSlot = m_pGameMgr->F_GetWidgetMgr()->F_GetBPRewardSlot();

	Box_QuestNotComplete->SetVisibility(ESlateVisibility::Visible);
	Box_QuestComplete->SetVisibility(ESlateVisibility::Hidden);

	Button_Reject->OnClicked.AddDynamic(this, &UQuestContent::OnButtonRejectClicked);
	Button_Accept->OnClicked.AddDynamic(this, &UQuestContent::OnButtonAcceptClicked);
	Button_Close->OnClicked.AddDynamic(this, &UQuestContent::OnButtonCancleClicked);
	Button_Complete->OnClicked.AddDynamic(this, &UQuestContent::OnButtonCompleteClicked);

}

void UQuestContent::ClearQuestObjectiveList()
{
	ObjectiveList->ClearChildren();
}

bool UQuestContent::CheckQuestComplete()
{
	bool AllObjectivesComplete = true;
	TArray<FQuestObjectiveData>* arQuestObjectiveData = m_Quest->F_GetObjectiveData();
	for (uint8 i = 0; i < (*arQuestObjectiveData).Num(); i++)
	{
		if (!(*arQuestObjectiveData)[i].m_bComplete)
		{
			AllObjectivesComplete = false;
		}
	}
	return AllObjectivesComplete;
}

void UQuestContent::Reward()
{
	m_Quest->F_Reward();
}

void UQuestContent::UpdateRewardBox(AQuest* Quest)
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

URewardSlot* UQuestContent::CreateRewardItemSlot(FItemData* ItemData)
{
	URewardSlot* pNewRewardSlot = CreateWidget<URewardSlot>(this, W_RewardSlot);
	pNewRewardSlot->F_SetItemData(ItemData);
	return pNewRewardSlot;
;}

void UQuestContent::F_SetQuestInfo(AQuest* Quest)
{
	ClearQuestObjectiveList();
	m_Quest = Quest;
	Text_QuestName->SetText(*m_Quest->F_GetName());
	Text_QuestDescription->SetText(*m_Quest->F_GetDescription());
	UpdateRewardBox(Quest);
	TArray<FQuestObjectiveData>* arQuestObjectiveData = m_Quest->F_GetObjectiveData();
	for (uint8 i = 0; i < (*arQuestObjectiveData).Num(); i++)
	{
		UQuestObjectiveItem* NewObjectiveItem = CreateWidget<UQuestObjectiveItem>(this, W_QuestObjectiveItem);
		NewObjectiveItem->F_SetQuestObjectiveInfo(&(*arQuestObjectiveData)[i]);
		ObjectiveList->AddChild(NewObjectiveItem);
	}	
	if (!m_Quest->F_GetbAccept())
	{
		Box_QuestNotComplete->SetVisibility(ESlateVisibility::Visible);
		Box_QuestComplete->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Box_QuestNotComplete->SetVisibility(ESlateVisibility::Hidden);
		Box_QuestComplete->SetVisibility(ESlateVisibility::Visible);
	}
	bool bQuestComplete = CheckQuestComplete();
	if (bQuestComplete)
	{
		Button_Complete->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Button_Complete->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UQuestContent::OnButtonRejectClicked()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestContent);
}

void UQuestContent::OnButtonAcceptClicked()
{
	m_Quest->F_SetbAccept(true);
	m_pGameMgr->F_GetQuestLogComponent()->F_AddQuestToLog(m_Quest);
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestContent);
	Cast<ANPC>(m_Quest->GetAttachParentActor())->F_DisplayTextRenderHasQuest(false);
	Box_QuestNotComplete->SetVisibility(ESlateVisibility::Hidden);
	Box_QuestComplete->SetVisibility(ESlateVisibility::Visible);
	Button_Complete->SetVisibility(ESlateVisibility::Hidden);
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundQuestAccept);
}

void UQuestContent::OnButtonCancleClicked()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestContent);
}

void UQuestContent::OnButtonCompleteClicked()
{
	m_Quest->F_SetbComplete(true);
	Reward();
	UQuestLog* QuestLog = m_pGameMgr->F_GetQuestLogComponent();
	TArray<AQuest*>* arQuest = QuestLog->F_GetarQuest();
	(*arQuest).Remove(m_Quest);
	if (QuestLog->F_GetActiveQuest() == m_Quest)
	{
		QuestLog->F_SetActiveQuest(nullptr);
	}
	m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetQuestObjectives()->F_UpdateObjectives();
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuestWindow()->DELE_UpdateActiveQuest.Broadcast();
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestContent);
	Cast<ANPC>(m_Quest->GetAttachParentActor())->F_QuestComplete();
	m_pGameMgr->F_NPCUpdateTextRenderHasQuest();
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundQuestComplete);
}

