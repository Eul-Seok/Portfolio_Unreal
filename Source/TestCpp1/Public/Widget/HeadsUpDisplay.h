// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget/InteractionAlert.h"
#include "HeadsUpDisplay.generated.h"

class ASkill_Base;

UCLASS()
class TESTCPP1_API UHeadsUpDisplay : public UUserWidget
{
	GENERATED_BODY()
public:
	UHeadsUpDisplay(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UBorder* MainBorder;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* WindowPanel;
	UPROPERTY(meta = (BindWidget))
	class UTargetBar* W_TargetBar;
	UPROPERTY(meta = (BindWidget))
	class UActionBar* W_ActionBar;
	UPROPERTY(meta = (BindWidget))
	class UCastBar* W_CastBar;
	UPROPERTY(meta = (BindWidget))
	class UInteractionAlert* W_InteractionAlert;
	UPROPERTY(meta = (BindWidget))
	class UConfirmWindow* W_ConfirmWindow;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_UI;
	UPROPERTY(meta = (BindWidget))
	class UQuestObjectives* W_QuestObjectives;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Alert;
	UPROPERTY(meta = (BindWidget))
	class UBuffPanel* W_BuffPanel;
	UPROPERTY(meta = (BindWidget))
	class UGameEndMenu* W_GameEndMenu;


protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	FTimerHandle m_TextAlertTimer;

protected:
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:
	void HiddenTextAlert();

public:
	class UCastBar* F_DisplayCastBar(ASkill_Base* SkilltoCast);
	void F_DisplayInteractionAlert(bool bDisplay, EInteractionAlertType InteractionAlertType);
	void F_DisplayConfirmWindow(bool bDisplay);
	void F_DisplayTextAlert(FText* Text);

public:
	FORCEINLINE UCanvasPanel* F_GetWindowPanel() const { return WindowPanel; }
	FORCEINLINE UTargetBar* F_GetTargetBar() const { return W_TargetBar; }
	FORCEINLINE UCanvasPanel* F_GetCanvasPanelUI() const { return CanvasPanel_UI; }
	FORCEINLINE UConfirmWindow* F_GetConfirmWindow() const { return W_ConfirmWindow; }
	FORCEINLINE UQuestObjectives* F_GetQuestObjectives() const { return W_QuestObjectives; }
	FORCEINLINE UBuffPanel* F_GetBuffPanel() const { return W_BuffPanel; }
	FORCEINLINE UGameEndMenu* F_GetGameEndMenu() const { return W_GameEndMenu; }
};
