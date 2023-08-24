// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

class UWidget;

UENUM(BlueprintType)
enum class EUIType : uint8
{
	E_Default = 0		UMETA(DisplayName = Default),
	E_StatusWindow		UMETA(DisplayName = StatusWindow),
	E_Inventory			UMETA(DisplayName = Inventory),
	E_SkillWindow 		UMETA(DisplayName = SkillWindow),
	E_QuestWindow 		UMETA(DisplayName = QuestWindow),
	E_QuestContent 		UMETA(DisplayName = QuestContent),
	E_UITypeMax			UMETA(DisplayName = Max)
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API UWidgetManager : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UWidgetManager();

protected:
	UPROPERTY()
	TSubclassOf<class UHeadsUpDisplay> W_HUD;
	UPROPERTY()
	TSubclassOf<class UInventory> W_Inventory;
	UPROPERTY()
	TSubclassOf<class USlot_Base> W_InventorySlot;
	UPROPERTY()
	TSubclassOf<class UQuickSlotWindow> W_QuickSlotWindow;
	UPROPERTY()
	TSubclassOf<class USlot_Base> W_QuickSlot;
	UPROPERTY()
	TSubclassOf<class USkillWindow> W_SkillWindow;
	UPROPERTY()
	TSubclassOf<class USlot_Base> W_SkillSlot;
	UPROPERTY()
	TSubclassOf<class USkillToolTip> W_SkillToolTip;
	UPROPERTY()
	TSubclassOf<class UItemPopUp> W_ItemPopUp;
	UPROPERTY()
	TSubclassOf<class UItemToolTip> W_ItemToolTip;
	UPROPERTY()
	TSubclassOf<class UDragIcon> W_DragIcon;
	UPROPERTY()
	TSubclassOf<class UStatusWindow> W_StatusWindow;
	UPROPERTY()
	TSubclassOf<class UQuestWindow> W_QuestWindow;
	UPROPERTY()
	TSubclassOf<class UQuestContent> W_QuestContent;
	UPROPERTY()
	TSubclassOf<class UQuestObjectiveItem> W_QuestObjectiveItem;
	UPROPERTY()
	TSubclassOf<class UQuestLogEntry> W_QuestLogEntry;
	UPROPERTY()
	TSubclassOf<class UQuestSingleObjective> W_QuestSingleObjective;
	UPROPERTY()
	TSubclassOf<class UBuffIcon> W_BuffIcon;
	UPROPERTY()
	TSubclassOf<class UPauseMenu> W_PauseMenu;
	UPROPERTY()
	TSubclassOf<class USlot_Base> W_RewardSlot;

protected:
	class AGameMgr* m_pGameMgr;
	class AMyPlayerController* m_PlayerController;
	UPROPERTY()
	class UHeadsUpDisplay* m_pHUD;
	UPROPERTY()
	class UInventory* m_pInventory;
	UPROPERTY()
	class USkillWindow* m_pSkillWindow;
	UPROPERTY()
	class UQuickSlotWindow* m_pQuickSlotWindow;
	UPROPERTY()
	class UTargetBar* m_TargetBar;
	UPROPERTY()
	class UStatusWindow* m_StatusWindow;
	UPROPERTY()
	class UQuestWindow* m_pQuestWindow;
	UPROPERTY()
	class UQuestContent* m_pQuestContent;
	UPROPERTY()
	class UPauseMenu* m_PauseMenu;

	bool m_bIsOpenedInventory;
	bool m_bIsOpenedSkillWindow;
	bool m_bIsOpenedStatusWindow;
	bool m_bIsOpenedQuestWindow;
	bool m_bIsOpenedQuestContent;
	bool m_bIsOpenedAnyUI;

	bool m_bIsOpenedPauseMenu;
	bool m_bIsOpenedRevivalMenu;
	bool m_bIsOpenedGameClearMenu;

	UPROPERTY()
	class UCanvasPanel* m_CanvasPanelUI;

protected:
	void ToggleInventory();
	void ToggleSkillWindow();
	void ToggleStatusWindow();
	void ToggleQuestWindow();
	void ToggleQuestContent();
	void AddCanvasPanelUI(UWidget* Widget);
	void CloseQuestWindow();
	void CloseQuestContent();

public:
	void F_Init();
	void F_ToggleUI(EUIType UIType);
	void F_TogglePauseMenu();
	void F_ToggleRevivalMenu();
	void F_ToggleGameClearMenu();
	void F_CloseAllUI();
	void F_DisplayHUD(bool bDislpay);
	void F_ShowGameMethod();

public:
	FORCEINLINE UHeadsUpDisplay* F_GetHUD() { return m_pHUD; }
	FORCEINLINE UInventory* F_GetInventory() { return m_pInventory; }
	FORCEINLINE USkillWindow* F_GetSkillWindow() { return m_pSkillWindow; }
	FORCEINLINE UQuickSlotWindow* F_GetQuickSlotWindow() { return m_pQuickSlotWindow; }
	FORCEINLINE UQuestContent* F_GetQuestContent() { return m_pQuestContent; }
	FORCEINLINE UQuestWindow* F_GetQuestWindow() { return m_pQuestWindow; }
	FORCEINLINE bool F_GetbOpenedAnyUI() { return m_bIsOpenedAnyUI; }

	FORCEINLINE TSubclassOf<USlot_Base> F_GetBPInventorySlot() { return W_InventorySlot; }
	FORCEINLINE TSubclassOf<USlot_Base> F_GetBPQuickSlot(){ return W_QuickSlot; }
	FORCEINLINE TSubclassOf<USlot_Base> F_GetBPSkillSlot(){ return W_SkillSlot; }
	FORCEINLINE TSubclassOf<USkillToolTip> F_GetBPSkillToolTip(){ return W_SkillToolTip; }
	FORCEINLINE TSubclassOf<UItemPopUp> F_GetBPItemPopUp(){ return W_ItemPopUp; }
	FORCEINLINE TSubclassOf<UItemToolTip> F_GetBPItemToolTip(){ return W_ItemToolTip; }
	FORCEINLINE TSubclassOf<UDragIcon> F_GetBPDragIcon(){ return W_DragIcon; }
	FORCEINLINE TSubclassOf<UQuestObjectiveItem> F_GetBPQuestObjectiveItem(){ return W_QuestObjectiveItem; }
	FORCEINLINE TSubclassOf<UQuestLogEntry> F_GetBPQuestLogEntry(){ return W_QuestLogEntry; }
	FORCEINLINE TSubclassOf<UQuestSingleObjective> F_GetBPQuestSingleObjective(){ return W_QuestSingleObjective; }
	FORCEINLINE TSubclassOf<UBuffIcon> F_GetBPBuffIcon(){ return W_BuffIcon; }
	FORCEINLINE TSubclassOf<USlot_Base> F_GetBPRewardSlot(){ return W_RewardSlot; }

public:
	FDele_Multi DELE_UpdateSkillSlotIconTint;
};


