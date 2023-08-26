// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/LocationMarker.h"
#include "Quest/QuestLog.h"
#include "Quest/Quest.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Manager/GameMgr.h"
#include "Manager/ItemManager.h"
#include "Manager/WidgetManager.h"
#include "Monster/MonsterSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Item/Item.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>
#include "Player/MyPlayerController.h"
#include "Widget/InventorySlot.h"


ALocationMarker::ALocationMarker():
	Scene_Root{}, LocationReachedCollision{}, m_pGameMgr{}, m_eLocationMarkerType{}, m_CheckItem{}, m_pMonsterSpawner{}, m_LevelSequenceActor{}
{
	PrimaryActorTick.bCanEverTick = false;
	Scene_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_Root"));
	RootComponent = Scene_Root;
	LocationReachedCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LocationReachedCollision"));
	LocationReachedCollision->SetupAttachment(Scene_Root);
	m_eLocationMarkerType = ELocationMarkerType::E_QuestLocation;
}

void ALocationMarker::BeginPlay()
{
	Super::BeginPlay();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	LocationReachedCollision->OnComponentBeginOverlap.AddDynamic(this, &ALocationMarker::OnOverlapBegin);
}

void ALocationMarker::PlayLevelSequence()
{
	if (m_eLocationMarkerType == ELocationMarkerType::E_LevelSequenceLoaction && m_LevelSequenceActor)
	{
		m_LevelSequenceActor->SequencePlayer->Play();
		m_LevelSequenceActor->SequencePlayer->OnFinished.AddDynamic(this, &ALocationMarker::MonsterSpawn);
		m_pGameMgr->F_GetWidgetMgr()->F_DisplayHUD(false);
		Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->F_InputIgnoreToggle(true);
	}
}

void ALocationMarker::MonsterSpawn()
{
	if (m_eLocationMarkerType == ELocationMarkerType::E_LevelSequenceLoaction && m_LevelSequenceActor && m_pMonsterSpawner)
	{
		m_LevelSequenceActor->SequencePlayer->OnFinished.RemoveDynamic(this, &ALocationMarker::MonsterSpawn);
		m_pGameMgr->F_GetWidgetMgr()->F_DisplayHUD(true);
		m_pMonsterSpawner->F_MonsterSpawn();
		Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->F_InputIgnoreToggle(false);
	}
}

void ALocationMarker::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (m_eLocationMarkerType == ELocationMarkerType::E_QuestLocation)
		{
			UQuestLog* QuestLog = m_pGameMgr->F_GetQuestLogComponent();
			TArray<AQuest*>* arQuest = QuestLog->F_GetarQuest();
			for (uint8 i = 0; i < (*arQuest).Num(); i++)
			{
				(*arQuest)[i]->DELE_LocationReached.Broadcast(this);
			}
		}
		else if (m_eLocationMarkerType == ELocationMarkerType::E_LevelSequenceLoaction)
		{
			TArray<UInventorySlot*>* arInventorySlot = m_pGameMgr->F_GetItemMgr()->F_GetInventorySlotArray();
			uint8 nArrayLength = m_pGameMgr->F_GetInventoryMgr()->F_GetLength();
			for (uint8 i = 0; i < nArrayLength; i++)
			{
				if ((*arInventorySlot)[i]->F_GetItemData()->m_ItemClass == m_CheckItem)
				{
					m_pGameMgr->F_GetItemMgr()->F_ItemUse(i);
					PlayLevelSequence();
					return;
				}
			}
		}
	}
}
