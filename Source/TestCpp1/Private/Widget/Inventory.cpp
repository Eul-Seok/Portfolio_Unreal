// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory.h"
#include "Manager/GameMgr.h"
#include "Manager/InventoryManager.h"
#include "Manager/WidgetManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/InventorySlot.h"
#include "Widget/ItemPopUp.h"
#include "Widget/SlotDragDropOperation.h"
#include "Widget/TitleBar.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"

UInventory::UInventory(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer), UniformGridPanel_Slot{}, m_pGameMgr{}, m_arInventorySlot{}, W_InventorySlot{}
{
}

void UInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	uint8 nLength = m_pGameMgr->F_GetInventoryMgr()->F_GetLength();
	uint8 nColumn = m_pGameMgr->F_GetInventoryMgr()->F_GetColumnCount();
	W_InventorySlot = m_pGameMgr->F_GetWidgetMgr()->F_GetBPInventorySlot();
	FItemData* ItemDataDefault = m_pGameMgr->F_GetInventoryMgr()->F_GetItemDataDefault();
	m_arInventorySlot.Reserve(nLength);
	for (uint8 Index = 0; Index < nLength; Index++)
	{
		CreateInventorySlot(Index / nColumn, Index % nColumn);
		m_arInventorySlot[Index]->F_SetInventoryIndex(Index);
		m_arInventorySlot[Index]->F_GetItemPopUp()->SetInventoryIndex(Index);
		m_arInventorySlot[Index]->F_SetItemData(ItemDataDefault);
		m_arInventorySlot[Index]->F_UpdateInventorySlotIcon();
	}
	W_TitleBar->F_GetTitleTextBlock()->SetText(FText::FromString(FString::Printf(TEXT("인벤토리"))));
}

void UInventory::NativeDestruct()
{
	Super::NativeDestruct();
	UWidgetBlueprintLibrary::CancelDragDrop();
}

void UInventory::CreateInventorySlot(uint8 Row, uint8 Column)
{
	UInventorySlot* pNewInventorySlot = CreateWidget<UInventorySlot>(this, W_InventorySlot);
	UniformGridPanel_Slot->AddChildToUniformGrid(pNewInventorySlot, Row, Column);
	m_arInventorySlot.Emplace(pNewInventorySlot);
}

