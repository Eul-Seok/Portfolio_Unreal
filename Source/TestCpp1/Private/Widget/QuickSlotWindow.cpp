// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Widget/Slot_Base.h"
#include "Widget/SlotType.h"
#include "Manager/GameMgr.h"
#include "Manager/InventoryManager.h"
#include "Manager/ItemManager.h"
#include "Components/UniformGridPanel.h"
#include "Components/ProgressBar.h"

#include "Manager/SkillManager.h"

UQuickSlotWindow::UQuickSlotWindow(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UQuickSlotWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;

	W_QuickSlot = m_pGameMgr->F_GetWidgetMgr()->F_GetBPQuickSlot();
	m_pGameMgr->F_GetItemMgr()->DELE_InventoryItemDestroy.BindUFunction(this, FName("F_CallResetQuickSlot"));
	uint8 nRow = 2;
	uint8 nColumn = 7;
	uint8 nLength = nRow * nColumn;
	m_arQuickSlot.Reserve(nLength);
	for (uint8 Index = 0; Index < nLength; Index++)
	{
		CreateQuickSlot(Index / nColumn, Index % nColumn);
		m_arQuickSlot[Index]->F_SetQuickSlotNumber((EQuickSlotNumber)(1+Index));
		m_arQuickSlot[Index]->F_SetQuickSlotIndex(Index);
		m_arQuickSlot[Index]->F_ResetQuickSlot();
		m_arQuickSlot[Index]->F_UpdateQuickSlotIcon();
	}
}

void UQuickSlotWindow::CreateQuickSlot(uint8 Row, uint8 Column)
{
	UQuickSlot* pNewQuickSlot = (CreateWidget<UQuickSlot>(this, W_QuickSlot));
	UniformGridPanel_Slot->AddChildToUniformGrid(pNewQuickSlot, Row, Column);
	m_arQuickSlot.Emplace(pNewQuickSlot);

}

void UQuickSlotWindow::F_QuickSlotUse(uint8 QuickSlotIndex)
{
	m_arQuickSlot[QuickSlotIndex]->F_QuickUse();
}

void UQuickSlotWindow::F_QuickSlotDataSwap(uint8 Dst, uint8 Src)
{
	ESlotType eDstPairSlotType{};
	ESlotType eSrcPairSlotType{};
	EQuickSlotNumber eDstQuickSlotNumber{};
	EQuickSlotNumber eSrcQuickSlotNumber{};
	UQuickSlot::S_QUICKSLOTDATA sTmpQuickSlotData{};
	ESlateVisibility eTmpDstCooldownBarVisibility{};

	eDstPairSlotType = m_arQuickSlot[Dst]->F_GetQuickSlotData()->m_ePairSlotType;
	eSrcPairSlotType = m_arQuickSlot[Src]->F_GetQuickSlotData()->m_ePairSlotType;
	eDstQuickSlotNumber = m_arQuickSlot[Dst]->F_GetQuickSlotNumber();
	eSrcQuickSlotNumber = m_arQuickSlot[Src]->F_GetQuickSlotNumber();

	if (eSrcPairSlotType == ESlotType::E_InventorySlot)
	{
		m_pGameMgr->F_GetInventoryMgr()->F_SetQuickSlotMap(m_arQuickSlot[Src]->F_GetQuickSlotData()->m_nPairSlotIndex, eDstQuickSlotNumber);
	}
	else if (eSrcPairSlotType == ESlotType::E_SkillSlot)
	{
		m_pGameMgr->F_GetSkillMgr()->F_SetQuickSlotMap(m_arQuickSlot[Src]->F_GetQuickSlotData()->m_nPairSlotIndex, eDstQuickSlotNumber);
	}
	if (eDstPairSlotType == ESlotType::E_InventorySlot)
	{
		m_pGameMgr->F_GetInventoryMgr()->F_SetQuickSlotMap(m_arQuickSlot[Dst]->F_GetQuickSlotData()->m_nPairSlotIndex, eSrcQuickSlotNumber);
	}
	else if (eDstPairSlotType == ESlotType::E_SkillSlot)
	{
		m_pGameMgr->F_GetSkillMgr()->F_SetQuickSlotMap(m_arQuickSlot[Dst]->F_GetQuickSlotData()->m_nPairSlotIndex, eSrcQuickSlotNumber);
	}

	sTmpQuickSlotData = *m_arQuickSlot[Dst]->F_GetQuickSlotData();
	m_arQuickSlot[Dst]->F_SetQuickSlotData(m_arQuickSlot[Src]->F_GetQuickSlotData());
	m_arQuickSlot[Src]->F_SetQuickSlotData(&sTmpQuickSlotData);
	
	eTmpDstCooldownBarVisibility = m_arQuickSlot[Dst]->CooldownBar->Visibility;
	m_arQuickSlot[Dst]->CooldownBar->SetVisibility(m_arQuickSlot[Src]->CooldownBar->Visibility);
	m_arQuickSlot[Src]->CooldownBar->SetVisibility(eTmpDstCooldownBarVisibility);

	m_arQuickSlot[Dst]->F_UpdateQuickSlotIcon();
	m_arQuickSlot[Src]->F_UpdateQuickSlotIcon();
}

TArray<UQuickSlot*>* UQuickSlotWindow::F_GetQuickSlotArray()
{
	return &m_arQuickSlot;
}

void UQuickSlotWindow::F_CallResetQuickSlot(uint8 PairIndex)
{
	EQuickSlotNumber PairQuickSlotNumber = m_pGameMgr->F_GetInventoryMgr()->F_GetQuickSlotMapValue(PairIndex);
	if (PairQuickSlotNumber != EQuickSlotNumber::E_Default)
	{
		uint8 PairQuickSlotIndex = (int)PairQuickSlotNumber - 1;
		m_arQuickSlot[PairQuickSlotIndex]->F_ResetQuickSlot();
		m_arQuickSlot[PairQuickSlotIndex]->F_UpdateQuickSlotIcon();
	}
}

