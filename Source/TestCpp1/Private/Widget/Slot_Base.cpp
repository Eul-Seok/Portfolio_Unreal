// Fill out your copyright notice in the Description page of Project Settings.



#include "Widget/Slot_Base.h"
#include "UObject/ConstructorHelpers.h"
#include "Input/Reply.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Widget/SlotDragDropOperation.h"
#include "Player/TestCpp1Character.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"

USlot_Base::USlot_Base(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), Image_Item{}, Image_Back{}, Image_Over{}, Image_Down{}, Border_InvenEvent{},
	m_eSlotType{}, m_pGameMgr{}, m_Player{}, m_PlayerController{}, W_DragIcon{}
{	
}

void USlot_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	W_DragIcon = m_pGameMgr->F_GetWidgetMgr()->F_GetBPDragIcon();
}

void USlot_Base::NativeConstruct()
{
	Super::NativeConstruct();
	Image_Over->SetVisibility(ESlateVisibility::Hidden);
	Image_Down->SetVisibility(ESlateVisibility::Hidden);
}

FReply USlot_Base::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	Image_Down->SetVisibility(ESlateVisibility::Hidden);
	return FReply::Handled();
}

void USlot_Base::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	Image_Over->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMouseEnter);
}

void USlot_Base::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	Image_Over->SetVisibility(ESlateVisibility::Hidden);
	Image_Down->SetVisibility(ESlateVisibility::Hidden);
}

bool USlot_Base::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	Image_Down->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	return true;
}

void USlot_Base::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	USlotDragDropOperation* Operation = Cast<USlotDragDropOperation>(InOperation);
	if (Operation)
	{
		if (Operation->F_GetDragBeginSlot() != this)
		{
			Image_Down->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	Image_Over->SetVisibility(ESlateVisibility::Hidden);
}

void USlot_Base::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	USlotDragDropOperation* Operation = Cast<USlotDragDropOperation>(InOperation);
	if (Operation)
	{
		Operation->F_GetDragBeginSlot()->F_GetImageDown()->SetVisibility(ESlateVisibility::Hidden);
	}
}

