// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestObjectives.h"
#include "Widget/QuestSingleObjective.h"
#include "Widget/QuestWindow.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Quest/QuestLog.h"
#include "Quest/Quest.h"
#include "Components/VerticalBox.h"

UQuestObjectives::UQuestObjectives(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuestObjectives::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	W_QuestSingleObjective = m_pGameMgr->F_GetWidgetMgr()->F_GetBPQuestSingleObjective();
	m_QuestLog = m_pGameMgr->F_GetQuestLogComponent();
	F_UpdateObjectives();
}

void UQuestObjectives::F_UpdateObjectives()
{
	ObjectiveList->ClearChildren();
	AQuest* ActiveQuest = m_QuestLog->F_GetActiveQuest();
	if (ActiveQuest)
	{
		TArray<FQuestObjectiveData>* arQuestObjectiveData = ActiveQuest->F_GetObjectiveData();
		for (uint8 i = 0; i < (*arQuestObjectiveData).Num(); i++)
		{
			UQuestSingleObjective* NewSingleObjective = CreateWidget<UQuestSingleObjective>(this, W_QuestSingleObjective);
			NewSingleObjective->F_SetObjectiveData(&(*arQuestObjectiveData)[i]);
			ObjectiveList->AddChild(NewSingleObjective);
		}
	}
}
