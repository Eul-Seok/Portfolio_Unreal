// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestObjectiveItem.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"

UQuestObjectiveItem::UQuestObjectiveItem(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuestObjectiveItem::F_SetQuestObjectiveInfo(FQuestObjectiveData* pObjectiveData)
{
	Text_Description->SetText(pObjectiveData->m_Description);
	if (pObjectiveData->m_bComplete)
	{
		CheckBox_Complete->SetIsChecked(true);
	}
}
