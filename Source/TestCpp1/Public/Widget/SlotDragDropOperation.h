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
	
public:
	ESlotType m_eDragBeginSlotType;
	uint8 m_nDragBeginIndex;
	UPROPERTY()
	class USlot_Base* m_pDragBeginSlot;
};
