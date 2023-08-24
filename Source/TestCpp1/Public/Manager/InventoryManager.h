// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/ItemData.h"
#include "Widget/QuickSlotNumber.h"
#include "InventoryManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API UInventoryManager : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UInventoryManager();

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	uint8 m_nItemRowCount;
	UPROPERTY()
	uint8 m_nItemColumnCount;
	UPROPERTY()
	uint8 m_nLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* m_pItemDataTable;
	UPROPERTY()
	TMap<uint8, EQuickSlotNumber> m_QuickSlotMap;
	
	FItemData* m_pItemDataDefault;

public:
	void F_Init(uint8 InventoryRow, uint8 InventoryColumn);
	bool F_ItemAdd(FName* ItemName);
	void F_ItemSwap(uint8 Dst, uint8 Src);
	void F_SetQuickSlotMap(uint8 InventoryIndex, EQuickSlotNumber QuickSlotNumber);

public:
	FORCEINLINE UDataTable* F_GetItemDataTable() { return m_pItemDataTable; }
	FORCEINLINE FItemData* F_GetItemDataDefault() { return m_pItemDataDefault; }
	FORCEINLINE uint8 F_GetLength() { return m_nLength; }
	FORCEINLINE uint8 F_GetRowCount() { return m_nItemRowCount; }
	FORCEINLINE uint8 F_GetColumnCount() { return m_nItemColumnCount; }
	FORCEINLINE uint8 F_GetQuickSlotMapKey(EQuickSlotNumber QuickSlotNumber) { return *m_QuickSlotMap.FindKey(QuickSlotNumber); }
	FORCEINLINE EQuickSlotNumber F_GetQuickSlotMapValue(uint8 InventoryIndex) { return m_QuickSlotMap[InventoryIndex]; }
	TArray<class UInventorySlot*>* F_GetInventorySlotArray();
	bool F_GetIsEnableItem(uint8 Index);
};
