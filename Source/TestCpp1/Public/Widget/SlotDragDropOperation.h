// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Slot_Base.h"
#include "SlotDragDropOperation.generated.h"

UCLASS()
class TESTCPP1_API USlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
protected:
	ESlotType m_eDragBeginSlotType;
	uint8 m_nDragBeginIndex;
	UPROPERTY()
	class USlot_Base* m_pDragBeginSlot;

public:
	void F_SetDragBeginSlotType(ESlotType eDragBeginSlotType);
	void F_SetDragBeginIndex(uint8 nDragBeginIndex);
	void F_SetDragBeginSlot(USlot_Base* pDragBeginSlot);

public:
	FORCEINLINE ESlotType F_GetDragBeginSlotType() const { return m_eDragBeginSlotType; }
	FORCEINLINE uint8 F_GetDragBeginIndex() const { return m_nDragBeginIndex; }
	FORCEINLINE USlot_Base* F_GetDragBeginSlot() const { return m_pDragBeginSlot; }
	
};
