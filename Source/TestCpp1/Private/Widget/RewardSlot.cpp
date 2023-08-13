// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RewardSlot.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/InventoryManager.h"
#include "Widget/ItemToolTip.h"
#include "Item/ItemData.h"
#include "Components/Image.h"

URewardSlot::URewardSlot(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void URewardSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CreateToolTip();
}

void URewardSlot::CreateToolTip()
{
	W_ItemToolTip = m_pGameMgr->F_GetWidgetMgr()->F_GetBPItemToolTip();
	m_pItemToolTip = CreateWidget<UItemToolTip>(GetWorld(), W_ItemToolTip);
	SetToolTip(m_pItemToolTip);
}

void URewardSlot::F_SetItemData(FItemData* pItemData)
{
	UTexture2D* Icon = pItemData->m_ItemImage;;
	Image_Item->SetBrushFromTexture(Icon);
	m_pItemToolTip->F_SetItemData(pItemData);
}
