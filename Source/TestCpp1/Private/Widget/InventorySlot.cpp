
#include "Widget/InventorySlot.h"
#include "Widget/Inventory.h"
#include "Widget/ItemPopUp.h"
#include "Widget/ItemToolTip.h"
#include "Widget/DragIcon.h"
#include "Widget/SlotDragDropOperation.h"
#include "Widget/HeadsUpDisplay.h"
#include "Components/Image.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/InventoryManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), m_nInventoryIndex{}, W_ItemPopUp{}, m_pItemPopUp{}, m_pItemData{}
{
}

void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_eSlotType = ESlotType::E_InventorySlot;
	CreateItemPopUp();
	F_CreateToolTip();
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (m_pGameMgr->F_GetInventoryMgr()->F_GetIsEnableItem(m_nInventoryIndex))
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			if (m_pItemData->m_ItemType == EItemType::E_Quest)
			{
				FText AlertText = FText::FromString(FString::Printf(TEXT("퀘스트 관련 아이템은 아이템 팝업을 띄울 수 없습니다")));
				m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
				m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
				return FReply::Unhandled();
			}
			float LocationX{};
			float LocationY{};
			m_PlayerController->GetMousePosition(LocationX, LocationY);
			if (!m_pItemPopUp->IsVisible())
			{
				m_pItemPopUp->SetPositionInViewport(FVector2D(LocationX - 50, LocationY - 10));
				m_pItemPopUp->SetVisibility(ESlateVisibility::Visible);
				return FReply::Handled();
			}
		}
		Image_Down->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMouseButtonDown);
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Unhandled();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragIcon* pNewDragIcon = CreateWidget<UDragIcon>(this, W_DragIcon);
	pNewDragIcon->m_pDragImage = Image_Item->Brush.GetResourceObject();
	USlotDragDropOperation* pDragDropOperation = Cast<USlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDropOperation::StaticClass()));
	if (pDragDropOperation)
	{
		pDragDropOperation->DefaultDragVisual = pNewDragIcon;
		pDragDropOperation->m_eDragBeginSlotType = m_eSlotType;
		pDragDropOperation->m_nDragBeginIndex = m_nInventoryIndex;
		pDragDropOperation->m_pDragBeginSlot = this;
		OutOperation = pDragDropOperation;
	}
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	USlotDragDropOperation* Operation = Cast<USlotDragDropOperation>(InOperation);
	if (Operation)
	{
		if (Operation->m_eDragBeginSlotType == m_eSlotType)
		{
			m_pGameMgr->F_GetInventoryMgr()->F_ItemSwap(Operation->m_nDragBeginIndex, m_nInventoryIndex);
		}
		Operation->m_pDragBeginSlot->Image_Down->SetVisibility(ESlateVisibility::Hidden);
		Image_Down->SetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::PlaySound2D(GetWorld(), m_SoundDrop);
		return true;
	}
	else
	{
		return false;
	}
}

void UInventorySlot::CreateItemPopUp()
{
	W_ItemPopUp = m_pGameMgr->F_GetWidgetMgr()->F_GetBPItemPopUp();
	m_pItemPopUp = CreateWidget<UItemPopUp>(GetWorld(), W_ItemPopUp);
	m_pItemPopUp->SetVisibility(ESlateVisibility::Hidden);
	m_pItemPopUp->AddToViewport(4);
}

void UInventorySlot::F_CreateToolTip()
{
	W_ItemToolTip = m_pGameMgr->F_GetWidgetMgr()->F_GetBPItemToolTip();
	m_pItemToolTip = CreateWidget<UItemToolTip>(GetWorld(), W_ItemToolTip);
	SetToolTip(m_pItemToolTip);
}

void UInventorySlot::F_UpdateInventorySlotIcon()
{
	UTexture2D* Icon = m_pItemData->m_ItemImage;
	EItemType ItemType = m_pItemData->m_ItemType;
	m_pItemPopUp->F_SetItemPopUpInfo(ItemType);
	Image_Item->SetBrushFromTexture(Icon);
}

void UInventorySlot::F_SetInventoryIndex(uint8 Index)
{
	m_nInventoryIndex = Index;
}

void UInventorySlot::F_SetItemData(FItemData* ItemData)
{
	m_pItemData = ItemData;
	m_pItemToolTip->F_SetItemData(m_pItemData);
}

FItemData* UInventorySlot::F_GetItemData()
{
	return m_pItemData;
}

UItemPopUp* UInventorySlot::F_GetItemPopUp()
{
	return m_pItemPopUp;
}