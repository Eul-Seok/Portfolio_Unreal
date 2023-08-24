// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HeadsUpDisplay.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TestCpp1Character.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Widget/SlotDragDropOperation.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Widget/ConfirmWindow.h"
#include "Widget/SkillWindow.h"
#include "Widget/CastBar.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/ItemManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"


UHeadsUpDisplay::UHeadsUpDisplay(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UHeadsUpDisplay::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;
}

bool UHeadsUpDisplay::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	USlotDragDropOperation* Operation = Cast<USlotDragDropOperation>(InOperation);
	if (Operation)
	{
		Operation->m_pDragBeginSlot->Image_Down->SetVisibility(ESlateVisibility::Hidden);
		if (Operation->m_eDragBeginSlotType == ESlotType::E_QuickSlot)
		{
			TArray<UQuickSlot*>* arQuickSlot = m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_GetQuickSlotArray();
			uint8 nDragBeginIndex = Operation->m_nDragBeginIndex;
			(*arQuickSlot)[nDragBeginIndex]->F_QuickSlotRegistrationCancle();
			return true;
		}
		if (Operation->m_eDragBeginSlotType == ESlotType::E_InventorySlot)
		{
			uint8 nDragBeginIndex = Operation->m_nDragBeginIndex;
			m_pGameMgr->F_GetItemMgr()->F_ItemDrop(nDragBeginIndex);
			return true;
		}
		return true;
	}
	return false;
}

void UHeadsUpDisplay::HiddenTextAlert()
{
	Text_Alert->SetVisibility(ESlateVisibility::Hidden);
}

UCastBar* UHeadsUpDisplay::F_DisplayCastBar(ASkill_Base* SkilltoCast)
{
	W_CastBar->F_SetSkill(SkilltoCast);
	W_CastBar->F_StartCast();
	return W_CastBar;
}

void UHeadsUpDisplay::F_DisplayInteractionAlert(bool bDisplay, EInteractionAlertType InteractionAlertType)
{
	if (bDisplay)
	{
		W_InteractionAlert->SetVisibility(ESlateVisibility::Visible);
		W_InteractionAlert->F_Display(InteractionAlertType);
	}
	else
	{
		W_InteractionAlert->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHeadsUpDisplay::F_DisplayConfirmWindow(bool bDisplay)
{
	if (bDisplay)
	{
		W_ConfirmWindow->SetVisibility(ESlateVisibility::Visible);
		FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetMouseLocation(ViewportSize.X*0.5f, ViewportSize.Y * 0.5f);
		m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundOpenUI);
	}
	else
	{
		W_ConfirmWindow->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHeadsUpDisplay::F_DisplayTextAlert(FText* Text)
{
	GetWorld()->GetTimerManager().ClearTimer(m_TextAlertTimer);
	Text_Alert->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Text_Alert->SetText(*Text);
	GetWorld()->GetTimerManager().SetTimer(m_TextAlertTimer, this, &UHeadsUpDisplay::HiddenTextAlert, 3.0f, false);
}