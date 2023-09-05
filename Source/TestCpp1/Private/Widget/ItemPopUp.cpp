// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemPopUp.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Manager/GameMgr.h"
#include "Manager/ItemManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/InventoryManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/ConfirmWindow.h"
#include "Kismet/GameplayStatics.h"

UItemPopUp::UItemPopUp(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer), m_pGameMgr{}, m_InventoryIndex{}
{
}

void UItemPopUp::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;
	Button_Use->OnClicked.AddDynamic(this, &UItemPopUp::OnButtonUseClicked);
	Button_Drop->OnClicked.AddDynamic(this, &UItemPopUp::OnButtonDropClicked);
	Button_Destroy->OnClicked.AddDynamic(this, &UItemPopUp::OnButtonDestroyClicked);
}

void UItemPopUp::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemPopUp::OnButtonUseClicked()
{
	m_pGameMgr->F_GetItemMgr()->F_ItemUse(m_InventoryIndex);
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemPopUp::OnButtonDropClicked()
{
	m_pGameMgr->F_GetItemMgr()->F_ItemDrop(m_InventoryIndex);
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemPopUp::OnButtonDestroyClicked()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayConfirmWindow(true);
	m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetConfirmWindow()->DELE_ButtonYes.BindUFunction(this, FName("CallItemDestroy"));
	m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetConfirmWindow()->F_SetInventoryIndex(m_InventoryIndex);
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemPopUp::CallItemDestroy()
{
	m_pGameMgr->F_GetItemMgr()->F_ItemDestroy(m_InventoryIndex);
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundItemDestroy);
}

void UItemPopUp::F_SetInventoryIndex(uint8 Index)
{
	m_InventoryIndex = Index;
}

void UItemPopUp::F_SetItemPopUpInfo(EItemType ItemType)
{
	UseButtonText->SetText(FText::FromString(FString::Printf(TEXT("사용하기"))));
	if (ItemType == EItemType::E_Equipment)
	{
		UseButtonText->SetText(FText::FromString(FString::Printf(TEXT("장착하기"))));
	}
}

