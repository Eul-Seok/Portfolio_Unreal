// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestSingleObjective.h"
#include "Components/TextBlock.h"

UQuestSingleObjective::UQuestSingleObjective(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuestSingleObjective::SetQuestInfoText()
{
	Text_Description->SetText(m_ObjectiveData->m_Description);
	EQuestType QuestType = m_ObjectiveData->m_QuestType;
	if (QuestType == EQuestType::E_Kill || QuestType == EQuestType::E_Collect)
	{
		Text_AchievementCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), m_ObjectiveData->m_nAchievementCount, m_ObjectiveData->m_nNumber)));
	}
	else
	{
		Text_AchievementCount->SetText(FText::FromString(""));
	}
	if (m_ObjectiveData->m_bComplete)
	{
		Text_IsComplete->SetText(FText::FromString(FString::Printf(TEXT("(완료)"))));
	}
	else
	{
		Text_IsComplete->SetText(FText::FromString(FString::Printf(TEXT("(미완료)"))));
	}
}

void UQuestSingleObjective::F_SetObjectiveData(FQuestObjectiveData* ObjectiveData)
{
	m_ObjectiveData = ObjectiveData;
	SetQuestInfoText();
}
