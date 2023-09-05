// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SlotDragDropOperation.h"

void USlotDragDropOperation::F_SetDragBeginSlotType(ESlotType eDragBeginSlotType)
{
	m_eDragBeginSlotType = eDragBeginSlotType;
}

void USlotDragDropOperation::F_SetDragBeginIndex(uint8 nDragBeginIndex)
{
	m_nDragBeginIndex = nDragBeginIndex;
}

void USlotDragDropOperation::F_SetDragBeginSlot(USlot_Base* pDragBeginSlot)
{
	m_pDragBeginSlot = pDragBeginSlot;
}
