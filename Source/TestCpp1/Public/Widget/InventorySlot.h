#pragma once

#include "CoreMinimal.h"
#include "Widget/Slot_Base.h"
#include "InventorySlot.generated.h"

class UItemPopUp;
class UItemToolTip;

UCLASS()
class TESTCPP1_API UInventorySlot : public USlot_Base
{
	GENERATED_BODY()

public:
	UInventorySlot(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY()
	uint8 m_nInventoryIndex;
	UPROPERTY()
	TSubclassOf<UItemPopUp> W_ItemPopUp;
	UPROPERTY()
	TSubclassOf<UItemToolTip> W_ItemToolTip;
	UPROPERTY()
	class UItemPopUp* m_pItemPopUp;
	UPROPERTY()
	class UItemToolTip* m_pItemToolTip;
	FItemData* m_pItemData;

protected:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:
	void CreateItemPopUp();

public:
	void F_CreateToolTip();
	void F_UpdateInventorySlotIcon();
	void F_SetInventoryIndex(uint8 Index);
	void F_SetItemData(FItemData* ItemData);
	FItemData* F_GetItemData();
	UItemPopUp* F_GetItemPopUp();
};
