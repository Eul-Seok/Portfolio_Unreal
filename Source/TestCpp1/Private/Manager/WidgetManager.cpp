// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WidgetManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/MyPlayerController.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/RewardSlot.h"
#include "Widget/Inventory.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/SkillWindow.h"
#include "Widget/SkillToolTip.h"
#include "Widget/DragIcon.h"
#include "Widget/Slot_Base.h"
#include "Widget/ItemPopUp.h"
#include "Widget/ItemToolTip.h"
#include "Widget/TargetBar.h"
#include "Widget/StatusWindow.h"
#include "Widget/QuestWindow.h"
#include "Widget/QuestContent.h"
#include "Widget/QuestObjectiveItem.h"
#include "Widget/QuestSingleObjective.h"
#include "Widget/BuffIcon.h"
#include "Widget/PauseMenu.h"
#include "Widget/GameEndMenu.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Manager/GameMgr.h"


UWidgetManager::UWidgetManager():
	W_HUD{}, W_Inventory{}, W_InventorySlot{}, W_QuickSlotWindow{}, W_QuickSlot{}, W_SkillWindow{}, W_SkillSlot{}, W_SkillToolTip{},
	W_ItemPopUp{}, W_ItemToolTip{}, W_DragIcon{}, W_StatusWindow{},
	m_PlayerController{}, m_HUD{}, m_Inventory{}, m_SkillWindow{}, m_QuickSlotWindow{}, m_TargetBar{}, m_StatusWindow{},
	m_bIsOpenedInventory{}, m_bIsOpenedSkillWindow{}, m_bIsOpenedStatusWindow{}
{
	static ConstructorHelpers::FClassFinder<UHeadsUpDisplay> W_HeadsUpDisplay(TEXT("/Game/Widgets/W_HUD"));
	if (W_HeadsUpDisplay.Succeeded() && W_HeadsUpDisplay.Class != nullptr)
	{
		W_HUD = W_HeadsUpDisplay.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_HUD"));
	}

	static ConstructorHelpers::FClassFinder<UInventory> W_INVENTORY(TEXT("/Game/Widgets/W_Inventory"));
	if (W_INVENTORY.Succeeded() && W_INVENTORY.Class != nullptr)
	{
		W_Inventory = W_INVENTORY.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_INVENTORY"));
	}
	static ConstructorHelpers::FClassFinder<USlot_Base> W_INVENTORYSLOT(TEXT("/Game/Widgets/W_InventorySlot"));
	if (W_INVENTORYSLOT.Succeeded() && W_INVENTORYSLOT.Class != nullptr)
	{
		W_InventorySlot = W_INVENTORYSLOT.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_InventorySlot"));
	}
	static ConstructorHelpers::FClassFinder<UQuickSlotWindow> W_QUICKSLOTWINDOW(TEXT("/Game/Widgets/W_QuickSlotWindow"));
	if (W_QUICKSLOTWINDOW.Succeeded() && W_QUICKSLOTWINDOW.Class != nullptr)
	{
		W_QuickSlotWindow = W_QUICKSLOTWINDOW.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuickSlotWindow"));
	}
	static ConstructorHelpers::FClassFinder<USlot_Base> W_QUICKSLOT(TEXT("/Game/Widgets/W_QuickSlot"));
	if (W_QUICKSLOT.Succeeded() && W_QUICKSLOT.Class != nullptr)
	{
		W_QuickSlot = W_QUICKSLOT.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuickSlot"));
	}
	static ConstructorHelpers::FClassFinder<USkillWindow> W_SKILLWINDOW(TEXT("/Game/Widgets/W_SkillWindow"));
	if (W_SKILLWINDOW.Succeeded() && W_SKILLWINDOW.Class != nullptr)
	{
		W_SkillWindow = W_SKILLWINDOW.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_SkillWindow"));
	}
	static ConstructorHelpers::FClassFinder<USlot_Base> W_SKILLSLOT(TEXT("/Game/Widgets/W_SkillSlot"));
	if (W_SKILLSLOT.Succeeded() && W_SKILLSLOT.Class != nullptr)
	{
		W_SkillSlot = W_SKILLSLOT.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_SkillSlot"));
	}
	static ConstructorHelpers::FClassFinder<USkillToolTip> W_SKILLTOOLTIP(TEXT("/Game/Widgets/W_SkillToolTip"));
	if (W_SKILLTOOLTIP.Succeeded() && W_SKILLTOOLTIP.Class != nullptr)
	{
		W_SkillToolTip = W_SKILLTOOLTIP.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_SkillToolTip"));
	}
	static ConstructorHelpers::FClassFinder<UItemPopUp> W_ITEMPOPUP(TEXT("/Game/Widgets/W_ItemPopUp"));
	if (W_ITEMPOPUP.Succeeded() && W_ITEMPOPUP.Class != nullptr)
	{
		W_ItemPopUp = W_ITEMPOPUP.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_ItemPopUp"));
	}
	static ConstructorHelpers::FClassFinder<UItemToolTip> W_ITEMTOOLTIP(TEXT("/Game/Widgets/W_ItemToolTip"));
	if (W_ITEMTOOLTIP.Succeeded() && W_ITEMTOOLTIP.Class != nullptr)
	{
		W_ItemToolTip = W_ITEMTOOLTIP.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_ItemToolTip"));
	}
	static ConstructorHelpers::FClassFinder<UDragIcon> W_DRAGICON(TEXT("/Game/Widgets/W_DragIcon"));
	if (W_DRAGICON.Succeeded() && W_DRAGICON.Class != nullptr)
	{
		W_DragIcon = W_DRAGICON.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_DragIcon"));
	}
	static ConstructorHelpers::FClassFinder<UStatusWindow> W_STATUSWINDOW(TEXT("/Game/Widgets/W_StatusWindow"));
	if (W_STATUSWINDOW.Succeeded() && W_STATUSWINDOW.Class != nullptr)
	{
		W_StatusWindow = W_STATUSWINDOW.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_StatusWindow"));
	}
	static ConstructorHelpers::FClassFinder<UQuestWindow> W_QUESTWINDOW(TEXT("/Game/Widgets/W_QuestWindow"));
	if (W_QUESTWINDOW.Succeeded() && W_QUESTWINDOW.Class != nullptr)
	{
		W_QuestWindow = W_QUESTWINDOW.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuestWindow"));
	}
	static ConstructorHelpers::FClassFinder<UQuestContent> W_QUESTCONTENT(TEXT("/Game/Widgets/W_QuestContent"));
	if (W_QUESTCONTENT.Succeeded() && W_QUESTCONTENT.Class != nullptr)
	{
		W_QuestContent = W_QUESTCONTENT.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuestContent"));
	}
	static ConstructorHelpers::FClassFinder<UQuestObjectiveItem> W_QUESTOBJECTIVEITEM(TEXT("/Game/Widgets/W_QuestObjectiveItem"));
	if (W_QUESTOBJECTIVEITEM.Succeeded() && W_QUESTOBJECTIVEITEM.Class != nullptr)
	{
		W_QuestObjectiveItem = W_QUESTOBJECTIVEITEM.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuestObjectiveItem"));
	}
	static ConstructorHelpers::FClassFinder<UQuestLogEntry> W_QUESTLOGENTRY(TEXT("/Game/Widgets/W_QuestLogEntry"));
	if (W_QUESTLOGENTRY.Succeeded() && W_QUESTLOGENTRY.Class != nullptr)
	{
		W_QuestLogEntry = W_QUESTLOGENTRY.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuestLogEntry"));
	}
	static ConstructorHelpers::FClassFinder<UQuestSingleObjective> W_QUESTSINGLEOBJECTIVE(TEXT("/Game/Widgets/W_QuestSingleObjective"));
	if (W_QUESTSINGLEOBJECTIVE.Succeeded() && W_QUESTSINGLEOBJECTIVE.Class != nullptr)
	{
		W_QuestSingleObjective = W_QUESTSINGLEOBJECTIVE.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_QuestSingleObjective"));
	}
	static ConstructorHelpers::FClassFinder<UBuffIcon> W_BUFFICON(TEXT("/Game/Widgets/W_BuffIcon"));
	if (W_BUFFICON.Succeeded() && W_BUFFICON.Class != nullptr)
	{
		W_BuffIcon = W_BUFFICON.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_BuffIcon"));
	}
	static ConstructorHelpers::FClassFinder<UPauseMenu> W_PAUSEMENU(TEXT("/Game/Widgets/W_PauseMenu"));
	if (W_PAUSEMENU.Succeeded() && W_PAUSEMENU.Class != nullptr)
	{
		W_PauseMenu = W_PAUSEMENU.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_PauseMenu"));
	}

	static ConstructorHelpers::FClassFinder<USlot_Base> W_REWARDSLOT(TEXT("/Game/Widgets/W_RewardSlot"));
	if (W_REWARDSLOT.Succeeded() && W_REWARDSLOT.Class != nullptr)
	{
		W_RewardSlot = W_REWARDSLOT.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find W_RewardSlot"));
	}
}

void UWidgetManager::ToggleInventory()
{
	UCanvasPanelSlot* UCanvasPanelSlot{};
	if (!m_bIsOpenedInventory)
	{
		CloseQuestWindow();
		AddCanvasPanelUI(m_Inventory);
	}
	else
	{
		m_CanvasPanelUI->RemoveChild(m_Inventory);
	}
	m_bIsOpenedInventory = !m_bIsOpenedInventory;
}

void UWidgetManager::ToggleSkillWindow()
{
	UCanvasPanelSlot* UCanvasPanelSlot{};
	if (!m_bIsOpenedSkillWindow)
	{
		CloseQuestWindow();
		AddCanvasPanelUI(m_SkillWindow);
		if (DELE_UpdateSkillSlotIconTint.IsBound())
		{
			DELE_UpdateSkillSlotIconTint.Broadcast();
		}
	}
	else
	{
		m_CanvasPanelUI->RemoveChild(m_SkillWindow);
	}
	m_bIsOpenedSkillWindow = !m_bIsOpenedSkillWindow;
}

void UWidgetManager::ToggleStatusWindow()
{
	UCanvasPanelSlot* UCanvasPanelSlot{};
	if (!m_bIsOpenedStatusWindow)
	{
		CloseQuestWindow();
		AddCanvasPanelUI(m_StatusWindow);
	}
	else
	{
		m_CanvasPanelUI->RemoveChild(m_StatusWindow);
	}
	m_bIsOpenedStatusWindow = !m_bIsOpenedStatusWindow;
}

void UWidgetManager::ToggleQuestWindow()
{
	
	if (!m_bIsOpenedQuestWindow)
	{
		F_CloseAllUI();
		AddCanvasPanelUI(m_QuestWindow);
	}
	else
	{
		CloseQuestWindow();
	}
	m_bIsOpenedQuestWindow = !m_bIsOpenedQuestWindow;
}

void UWidgetManager::ToggleQuestContent()
{
	if (!m_bIsOpenedQuestContent)
	{
		F_CloseAllUI();
		AddCanvasPanelUI(m_QuestContent);
		m_PlayerController->F_InputIgnoreToggle(true);
	}
	else
	{
		CloseQuestContent();
		m_PlayerController->F_InputIgnoreToggle(false);
	}
	m_bIsOpenedQuestContent = !m_bIsOpenedQuestContent;
}

void UWidgetManager::AddCanvasPanelUI(UWidget* Widget)
{
	float fAnchorsHorizontal{};
	float fAnchorsVertical{};
	float AlignmentX{};
	float AlignmentY{};
	fAnchorsVertical = 0.5f;
	AlignmentY = 0.5f;
	if (Widget == m_StatusWindow|| Widget == m_QuestWindow || Widget == m_QuestContent || Widget == m_PauseMenu)
	{
		fAnchorsHorizontal = 0.5f;
		AlignmentX = 0.5f;
	}
	else if (Widget == m_SkillWindow)
	{
		fAnchorsHorizontal = 0.0f;
		AlignmentX = -0.1f;
	}
	else if (Widget == m_Inventory)
	{
		fAnchorsHorizontal = 1.0f;
		AlignmentX = 1.1f;
	}
	UCanvasPanelSlot* UCanvasPanelSlot{};
	UCanvasPanelSlot = m_CanvasPanelUI->AddChildToCanvas(Widget);
	UCanvasPanelSlot->SetAutoSize(true);
	UCanvasPanelSlot->SetAnchors(FAnchors(fAnchorsHorizontal, fAnchorsVertical));
	UCanvasPanelSlot->SetAlignment(FVector2D(AlignmentX, AlignmentY));
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundOpenUI);
}

void UWidgetManager::CloseQuestWindow()
{
	if (m_bIsOpenedQuestWindow)
	{
		m_QuestWindow->RemoveFromParent();
	}
}

void UWidgetManager::CloseQuestContent()
{
	if (m_bIsOpenedQuestContent)
	{
		m_QuestContent->RemoveFromParent();
	}
}

void UWidgetManager::F_Init()
{
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_HUD = CreateWidget<UHeadsUpDisplay>(GetWorld(), W_HUD);
	m_Inventory = CreateWidget<UInventory>(GetWorld(), W_Inventory);
	m_QuickSlotWindow = CreateWidget<UQuickSlotWindow>(GetWorld(), W_QuickSlotWindow);
	m_SkillWindow = CreateWidget<USkillWindow>(GetWorld(), W_SkillWindow);
	m_StatusWindow = CreateWidget<UStatusWindow>(GetWorld(), W_StatusWindow);
	m_QuestWindow = CreateWidget<UQuestWindow>(GetWorld(), W_QuestWindow);
	m_QuestContent = CreateWidget<UQuestContent>(GetWorld(), W_QuestContent);
	m_PauseMenu = CreateWidget<UPauseMenu>(GetWorld(), W_PauseMenu);


	m_HUD->AddToViewport(1);
	m_QuickSlotWindow->SetAnchorsInViewport(FAnchors(0.5f, 1.0f));
	m_QuickSlotWindow->SetAlignmentInViewport(FVector2D(0.5f, 1.0f));
	m_QuickSlotWindow->AddToViewport(2);

	m_CanvasPanelUI = m_HUD->F_GetCanvasPanelUI();
}

void UWidgetManager::F_ToggleUI(EUIType UIType)
{
	if (UIType == EUIType::E_SkillWindow)
	{
		ToggleSkillWindow();
	}
	else if (UIType == EUIType::E_StatusWindow)
	{
		ToggleStatusWindow();
	}
	else if (UIType == EUIType::E_Inventory)
	{
		ToggleInventory();
	}
	else if (UIType == EUIType::E_QuestWindow)
	{
		ToggleQuestWindow();
	}
	else if (UIType == EUIType::E_QuestContent)
	{
		ToggleQuestContent();
	}
	
	if (m_bIsOpenedSkillWindow || m_bIsOpenedStatusWindow || m_bIsOpenedInventory || m_bIsOpenedQuestWindow || m_bIsOpenedQuestContent)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(true);
		m_bIsOpenedAnyUI = true;
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(false);
		m_bIsOpenedAnyUI = false;
	}
}

void UWidgetManager::F_TogglePauseMenu()
{
	if (!m_bIsOpenedPauseMenu)
	{
		m_PauseMenu->AddToViewport(3);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(true);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		m_PauseMenu->RemoveFromViewport();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(false);
	}
	m_bIsOpenedPauseMenu = !m_bIsOpenedPauseMenu;
}

void UWidgetManager::F_ToggleRevivalMenu()
{
	if (!m_bIsOpenedRevivalMenu)
	{
		m_HUD->F_GetGameEndMenu()->SetVisibility(ESlateVisibility::Visible);
		m_HUD->F_GetGameEndMenu()->F_DisplayRevivalMenu();
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		m_HUD->F_GetGameEndMenu()->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(false);
	}
	m_bIsOpenedRevivalMenu = !m_bIsOpenedRevivalMenu;
}

void UWidgetManager::F_ToggleGameClearMenu()
{
	if (!m_bIsOpenedGameClearMenu)
	{
		m_HUD->F_GetGameEndMenu()->SetVisibility(ESlateVisibility::Visible);
		m_HUD->F_GetGameEndMenu()->F_DisplayGameClearMenu();
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(true);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		m_HUD->F_GetGameEndMenu()->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(m_PlayerController);
		m_PlayerController->SetShowMouseCursor(false);
	}
	m_bIsOpenedGameClearMenu = !m_bIsOpenedGameClearMenu;
}


void UWidgetManager::F_CloseAllUI()
{
	m_CanvasPanelUI->ClearChildren();
	m_bIsOpenedSkillWindow = false;
	m_bIsOpenedStatusWindow = false;
	m_bIsOpenedInventory = false;
	m_bIsOpenedQuestWindow = false;
	m_bIsOpenedQuestContent = false;
	m_bIsOpenedAnyUI = false;
	m_PlayerController->F_InputIgnoreToggle(false);
	m_HUD->F_DisplayConfirmWindow(false);

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(m_PlayerController);
	m_PlayerController->SetShowMouseCursor(false);
}

void UWidgetManager::F_DisplayHUD(bool bDislpay)
{
	if (bDislpay)
	{
		m_HUD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_QuickSlotWindow->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_HUD->SetVisibility(ESlateVisibility::Hidden);
		m_QuickSlotWindow->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidgetManager::F_ShowGameMethod()
{
	F_TogglePauseMenu();
	m_PauseMenu->F_OpenPanelGameMethod();
}

UHeadsUpDisplay* UWidgetManager::F_GetHUD()
{
	return m_HUD;
}

UInventory* UWidgetManager::F_GetInventory()
{
	return m_Inventory;
}

USkillWindow* UWidgetManager::F_GetSkillWindow()
{
	return m_SkillWindow;
}

UQuickSlotWindow* UWidgetManager::F_GetQuickSlotWindow()
{
	return m_QuickSlotWindow;
}

UQuestContent* UWidgetManager::F_GetQuestContent()
{
	return m_QuestContent;
}

UQuestWindow* UWidgetManager::F_GetQuestWindow()
{
	return m_QuestWindow;
}

bool UWidgetManager::F_GetbOpenedAnyUI()
{
	return m_bIsOpenedAnyUI;
}

TSubclassOf<USlot_Base> UWidgetManager::F_GetBPInventorySlot()
{
	return W_InventorySlot;
}

TSubclassOf<USlot_Base> UWidgetManager::F_GetBPQuickSlot()
{
	return W_QuickSlot;
}

TSubclassOf<USlot_Base> UWidgetManager::F_GetBPSkillSlot()
{
	return W_SkillSlot;
}

TSubclassOf<USkillToolTip> UWidgetManager::F_GetBPSkillToolTip()
{
	return W_SkillToolTip;
}

TSubclassOf<UItemPopUp> UWidgetManager::F_GetBPItemPopUp()
{
	return W_ItemPopUp;
}

TSubclassOf<UItemToolTip> UWidgetManager::F_GetBPItemToolTip()
{
	return W_ItemToolTip;
}

TSubclassOf<UDragIcon> UWidgetManager::F_GetBPDragIcon()
{
	return W_DragIcon;
}

TSubclassOf<UQuestObjectiveItem> UWidgetManager::F_GetBPQuestObjectiveItem()
{
	return W_QuestObjectiveItem;
}

TSubclassOf<UQuestLogEntry> UWidgetManager::F_GetBPQuestLogEntry()
{
	return W_QuestLogEntry;
}

TSubclassOf<UQuestSingleObjective> UWidgetManager::F_GetBPQuestSingleObjective()
{
	return W_QuestSingleObjective;
}

TSubclassOf<UBuffIcon> UWidgetManager::F_GetBPBuffIcon()
{
	return W_BuffIcon;
}

TSubclassOf<USlot_Base> UWidgetManager::F_GetBPRewardSlot()
{
	return W_RewardSlot;
}
