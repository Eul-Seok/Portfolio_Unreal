// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestLog.h"
#include "Quest/Quest.h"

UQuestLog::UQuestLog():
	m_arQuest{}, m_ActiveQuest{}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestLog::F_AddQuestToLog(AQuest* Quest)
{
	m_arQuest.AddUnique(Quest);
}

void UQuestLog::F_SetActiveQuest(AQuest* Quest)
{
	m_ActiveQuest = Quest;
}

TArray<AQuest*>* UQuestLog::F_GetarQuest()
{
	return &m_arQuest;
}

AQuest* UQuestLog::F_GetActiveQuest()
{
	return m_ActiveQuest;
}
