// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Quest.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/InventoryManager.h"
#include "Manager/SoundManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/QuestObjectives.h"
#include "Widget/QuestWindow.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "Item/Item.h"
#include "NPC/NPC.h"

AQuest::AQuest() :
	m_pGameMgr{}, m_Player{}, m_Name{}, m_Description{}, m_arObjectiveData{}, m_bStoryQuest{}, m_PreRequisiteQuest{},
	m_arRewardItem{}, m_RewardExp{}, m_nCurrentAchievementCount{}, m_bComplete{}, m_bAccept{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_bStoryQuest = true;
}

void AQuest::OrganiseQuestInEditor()
{
	if (m_QuestOwner)
	{
		AttachToActor(m_QuestOwner, FAttachmentTransformRules::KeepWorldTransform);
	}
	SetActorLocation(GetAttachParentActor()->GetActorLocation()); 
}

void AQuest::BeginPlay()
{
	Super::BeginPlay();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	DELE_LocationReached.AddUFunction(this, FName("CallCheckLocationObjective"));
	DELE_InteractionTarget.AddUFunction(this, FName("CallCheckInteractionObjective"));
	DELE_CollectedItem.AddUFunction(this, FName("CallCheckCollectionObjective"));
	DELE_KilledTarget.AddUFunction(this, FName("CallCheckKilledTargetObjective"));
}

void AQuest::CheckObjective(EQuestType QuestType, AActor* Target)
{
	bool bUpdateUI{};
	if (QuestType == EQuestType::E_Location || QuestType == EQuestType::E_Interact)
	{
		for (uint8 i = 0; i < m_arObjectiveData.Num(); i++)
		{
			if (!m_arObjectiveData[i].m_bComplete && m_arObjectiveData[i].m_Target == Target->GetClass())
			{
				m_arObjectiveData[i].m_bComplete = true;
				m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundQuestSingleObjectiveComplete);
				bUpdateUI = true;
			}
		}
	}
	else
	{
		for (uint8 i = 0; i < m_arObjectiveData.Num(); i++)
		{
			if (!m_arObjectiveData[i].m_bComplete && m_arObjectiveData[i].m_Target == Target->GetClass())
			{
				m_arObjectiveData[i].m_nAchievementCount++;
				if (m_arObjectiveData[i].m_nAchievementCount >= m_arObjectiveData[i].m_nNumber)
				{
					m_arObjectiveData[i].m_bComplete = true;
					m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundQuestSingleObjectiveComplete);
				}
				bUpdateUI = true;
			}
		}
	}
	if (bUpdateUI)
	{
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetQuestObjectives()->F_UpdateObjectives();
		m_pGameMgr->F_GetWidgetMgr()->F_GetQuestWindow()->F_CallUpdateActiveQuestInfo();
	}
}

void AQuest::CallCheckLocationObjective(AActor* LocationReached)
{
	CheckObjective(EQuestType::E_Location, LocationReached);
}

void AQuest::CallCheckInteractionObjective(AActor* InteractionTarget)
{
	CheckObjective(EQuestType::E_Interact, InteractionTarget);
}

void AQuest::CallCheckCollectionObjective(AActor* CollectedItem)
{
	CheckObjective(EQuestType::E_Collect, CollectedItem);
}

void AQuest::CallCheckKilledTargetObjective(AActor* KilledTarget)
{
	CheckObjective(EQuestType::E_Kill, KilledTarget);
}

void AQuest::F_Reward()
{
	bool bSucess{};
	for (uint8 i=0; i<m_arRewardItem.Num(); i++)
	{
		FName* RowName = m_arRewardItem[i].GetDefaultObject()->F_GetRowName();
		bSucess = m_pGameMgr->F_GetInventoryMgr()->F_ItemAdd(RowName);
		if (!bSucess)
		{
			FActorSpawnParameters SpawnParameters{};
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(m_arRewardItem[i], m_Player->GetActorTransform(), SpawnParameters);
			if (SpawnedItem)
			{
				SpawnedItem->GetStaticMeshComponent()->SetSimulatePhysics(true);
			}
		}
	}
	m_Player->F_GetPlayerStatusComponent()->F_AddExp(m_RewardExp);
}

void AQuest::F_SetbComplete(bool IsComplete)
{
	m_bComplete = IsComplete;
}

void AQuest::F_SetbAccept(bool IsAccept)
{
	m_bAccept = IsAccept;
}

FText* AQuest::F_GetName()
{
	return &m_Name;
}

FText* AQuest::F_GetDescription()
{
	return &m_Description;
}

TArray<FQuestObjectiveData>* AQuest::F_GetObjectiveData()
{
	return &m_arObjectiveData;
}

bool AQuest::F_GetbStoryQuest()
{
	return m_bStoryQuest;
}

bool AQuest::F_GetbComplete()
{
	return m_bComplete;
}

bool AQuest::F_GetbAccept()
{
	return m_bAccept;
}

uint8 AQuest::F_GetCurrentAchievementCount()
{
	return m_nCurrentAchievementCount;
}

AQuest* AQuest::F_GetPreRequisiteQuest()
{
	return m_PreRequisiteQuest;
}

TArray<TSubclassOf<class AItem>>* AQuest::F_GetarRewardItem()
{
	return &m_arRewardItem;
}

float AQuest::F_GetRewardExp()
{
	return m_RewardExp;
}
