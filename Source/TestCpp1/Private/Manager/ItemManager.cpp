// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ItemManager.h"
#include "Player/TestCpp1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/Inventory.h"
#include "Widget/InventorySlot.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Item/Item.h"
#include "Item/Weapon_Base.h"
#include "Manager/GameMgr.h"
#include "Manager/InventoryManager.h"
#include "Manager/AffectManager.h"
#include "Manager/WidgetManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/ConfirmWindow.h"
#include "Affect/Affect_base.h"


UItemManager::UItemManager():
	m_pGameMgr{}, m_Player{}, m_Interface_Affect{}
{
}

void UItemManager::F_Init()
{
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

bool UItemManager::F_ItemUse(uint8 Index)
{
	if ((*F_GetInventorySlotArray()).IsValidIndex(Index))
	{
		EItemType ItemType = (*F_GetInventorySlotArray())[Index]->F_GetItemData()->m_ItemType;
		if (ItemType == EItemType::E_Equipment)
		{
			TSubclassOf<AWeapon_Base> Weapon = (TSubclassOf<AWeapon_Base>)(*F_GetInventorySlotArray())[Index]->F_GetItemData()->m_ItemClass;
			m_Player->F_CreateWeapon(Weapon);
			F_ItemDestroy(Index);
			FText AlertText = FText::FromString(FString::Printf(TEXT("'V'를 눌러 무기를 착용해주세요")));
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
			return true;
		}
		bool bSuccess = ApplyAffect(Index);
		if (bSuccess)
		{
			if (ItemType == EItemType::E_Consumption)
			{
				m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDrink);
			}
			F_ItemDestroy(Index);
			return true;
		}
		else
		{
			m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool UItemManager::F_ItemDrop(uint8 Index)
{
	ItemSpawn(Index);
	F_ItemDestroy(Index);
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundItemDrop);
	return true;
}

bool UItemManager::F_ItemDestroy(uint8 Index)
{
	(*F_GetInventorySlotArray())[Index]->F_SetItemData(m_pGameMgr->F_GetInventoryMgr()->F_GetItemDataDefault());
	(*F_GetInventorySlotArray())[Index]->F_UpdateInventorySlotIcon();
	DELE_InventoryItemDestroy.ExecuteIfBound(Index);
	m_pGameMgr->F_GetInventoryMgr()->F_SetQuickSlotMap(Index, EQuickSlotNumber::E_Default);
	uint8 OpendInventoryIndexConfirmWindow = m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetConfirmWindow()->F_GetInventoryIndex();
	if (OpendInventoryIndexConfirmWindow == Index)
	{
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayConfirmWindow(false);
	}
	return true;
}

bool UItemManager::ApplyAffect(uint8 Index)
{
	
	EAffectType ItemAffect = (*F_GetInventorySlotArray())[Index]->F_GetItemData()->m_eAffectType;
	float ItemValueApplied = (*F_GetInventorySlotArray())[Index]->F_GetItemData()->m_fAffectValue;
	m_Interface_Affect = Cast<IInterface_Affect>(m_Player->F_GetGameMgr()->F_GetAffectMgr()->F_GetAffect(ItemAffect));
	bool bSuccess = m_Interface_Affect->F_Apply(m_Player, ItemValueApplied, EOperatorType::E_Plus);
	return bSuccess;
}

void UItemManager::ItemSpawn(uint8 Index)
{
	UWorld* world = GetWorld();
	TSubclassOf<AItem> SpawnClass = (*F_GetInventorySlotArray())[Index]->F_GetItemData()->m_ItemClass;
	FVector SpawnLocation = m_Player->GetActorLocation();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector ForceVector = m_Player->GetActorForwardVector() * 30000;

	AItem* SpawnedItem = world->SpawnActor<AItem>(SpawnClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
	SpawnedItem->GetStaticMeshComponent()->SetSimulatePhysics(true);
	SpawnedItem->GetStaticMeshComponent()->AddForce(ForceVector, "", true);
}

TArray<class UInventorySlot*>* UItemManager::F_GetInventorySlotArray()
{
	return m_pGameMgr->F_GetWidgetMgr()->F_GetInventory()->F_GetarInventorySlot();
}

