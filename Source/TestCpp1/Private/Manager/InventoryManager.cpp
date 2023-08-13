
#include "Manager/InventoryManager.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/Inventory.h"
#include "Widget/InventorySlot.h"
#include "Widget/Slot_Base.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Item/Item.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

UInventoryManager::UInventoryManager() :
	m_pGameMgr{}, m_nItemRowCount{}, m_nItemColumnCount{}, m_nLength{}, m_pItemDataTable{}, m_QuickSlotMap{}, m_pItemDataDefault{}
{
}

void UInventoryManager::F_Init(uint8 InventoryRow, uint8 InventoryColumn)
{
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_nItemRowCount = InventoryRow;
	m_nItemColumnCount = InventoryColumn;
	m_nLength = InventoryRow * InventoryColumn;
	m_pItemDataDefault = m_pItemDataTable->FindRow<FItemData>(FName("Default"), "");
	
	m_QuickSlotMap.Reserve(m_nLength);
	for (uint8 Index = 0; Index < m_nLength; Index++)
	{
		m_QuickSlotMap.Emplace(Index, EQuickSlotNumber::E_Default);
	}
}

bool UInventoryManager::F_ItemAdd(FName* ItemRowName)
{
	bool bSucess{};
	FItemData* newItemData = m_pItemDataTable->FindRow<FItemData>(*ItemRowName, "");
	for (uint8 Index = 0; Index < (*F_GetInventorySlotArray()).Num(); Index++)
	{
		if ((*F_GetInventorySlotArray())[Index]->F_GetItemData() == m_pItemDataDefault)
		{
			(*F_GetInventorySlotArray())[Index] -> F_SetItemData(newItemData);
			(*F_GetInventorySlotArray())[Index]->F_UpdateInventorySlotIcon();
			m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundItemPickUp);

			bSucess = true;
			return bSucess;
		}
	}
	if (!bSucess)
	{
		FText AlertText = FText::FromString(FString::Printf(TEXT("인벤토리가 가득 차 있습니다")));
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
	}
	return bSucess;
}


void UInventoryManager::F_ItemSwap(uint8 Dst, uint8 Src)
{
	EQuickSlotNumber DstQuickSlotNumber{};
	DstQuickSlotNumber = m_QuickSlotMap[Dst];
	if (DstQuickSlotNumber != EQuickSlotNumber::E_Default)
	{
		uint8 DstQuickSlotIndex = (int)DstQuickSlotNumber-1;
		(*m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_GetQuickSlotArray())[DstQuickSlotIndex]->F_GetQuickSlotData()->m_nPairSlotIndex = Src;
	}
	F_SetQuickSlotMap(Dst, m_QuickSlotMap[Src]);
	F_SetQuickSlotMap(Src, DstQuickSlotNumber);

	FItemData* Tmp{};
	Tmp = (*F_GetInventorySlotArray())[Dst]->F_GetItemData();
	(*F_GetInventorySlotArray())[Dst]->F_SetItemData((*F_GetInventorySlotArray())[Src]->F_GetItemData());
	(*F_GetInventorySlotArray())[Src]->F_SetItemData(Tmp);
	(*F_GetInventorySlotArray())[Dst]->F_UpdateInventorySlotIcon();
	(*F_GetInventorySlotArray())[Src]->F_UpdateInventorySlotIcon();
}

bool UInventoryManager::F_GetIsEnableItem(uint8 Index)
{
	return (*F_GetInventorySlotArray())[Index]->F_GetItemData()->m_IsEnable;
}

void UInventoryManager::F_SetQuickSlotMap(uint8 InventoryIndex, EQuickSlotNumber QuickSlotNumber)
{
	m_QuickSlotMap.Emplace(InventoryIndex, QuickSlotNumber);
}

UDataTable* UInventoryManager::F_GetItemDataTable()
{
	return m_pItemDataTable;
}

FItemData* UInventoryManager::F_GetItemDataDefault()
{
	return m_pItemDataDefault;
}


uint8 UInventoryManager::F_GetLength()
{
	return m_nLength;
}

uint8 UInventoryManager::F_GetRowCount()
{
	return m_nItemRowCount;
}

uint8 UInventoryManager::F_GetColumnCount()
{
	return m_nItemColumnCount;
}

uint8 UInventoryManager::F_GetQuickSlotMapKey(EQuickSlotNumber QuickSlotNumber)
{
	return *m_QuickSlotMap.FindKey(QuickSlotNumber);
}

EQuickSlotNumber UInventoryManager::F_GetQuickSlotMapValue(uint8 InventoryIndex)
{
	return m_QuickSlotMap[InventoryIndex];
}

TArray<UInventorySlot*>* UInventoryManager::F_GetInventorySlotArray()
{
	return m_pGameMgr->F_GetWidgetMgr()->F_GetInventory()->F_GetarInventorySlot();
}