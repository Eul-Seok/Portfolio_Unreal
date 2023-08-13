// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestLogEntry.h"
#include "Widget/QuestWindow.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/QuestObjectives.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Quest/Quest.h"
#include "Quest/QuestLog.h"

UQuestLogEntry::UQuestLogEntry(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuestLogEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	Button_Active->OnClicked.AddDynamic(this, &UQuestLogEntry::OnButtonActiveClicked);
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuestWindow()->DELE_UpdateActiveQuest.AddUFunction(this, FName("CallUpdateActiveSlate"));
}

void UQuestLogEntry::ActiveSlate()
{
	Border_Active->SetBrushColor(FLinearColor::Yellow);
	bActive = true;
}

void UQuestLogEntry::InactiveSlate()
{
	Border_Active->SetBrushColor(FLinearColor::Gray);
	bActive = false;
}

void UQuestLogEntry::CallUpdateActiveSlate()
{
	UQuestLog* QuestLog = m_pGameMgr->F_GetQuestLogComponent();
	if (QuestLog->F_GetActiveQuest() == m_Quest)
	{
		ActiveSlate();
	}
	else
	{
		InactiveSlate();
	}
}

void UQuestLogEntry::F_SetQuestInfo(AQuest* Quest)
{
	m_Quest = Quest;
	Text_QuestName->SetText(*m_Quest->F_GetName());
	CallUpdateActiveSlate();
}

void UQuestLogEntry::OnButtonActiveClicked()
{
	UQuestLog* QuestLog = m_pGameMgr->F_GetQuestLogComponent();
	QuestLog->F_SetActiveQuest(m_Quest);
	if (bActive)
	{
		QuestLog->F_SetActiveQuest(nullptr);
	}
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuestWindow()->DELE_UpdateActiveQuest.Broadcast();
	m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetQuestObjectives()->F_UpdateObjectives();	
}
