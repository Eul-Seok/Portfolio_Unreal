// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TitleBar.h"
#include "Widget/SkillWindow.h"
#include "Widget/StatusWindow.h"
#include "Widget/Inventory.h"
#include "Widget/QuestWindow.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UTitleBar::UTitleBar(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UTitleBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	Button_Close->OnClicked.AddDynamic(this, &UTitleBar::CloseWindow);
	Border_WindowBar->OnMouseButtonDownEvent.BindUFunction(this, FName("OnBorderMouserDown"));
	Border_WindowBar->OnMouseButtonUpEvent.BindUFunction(this, FName("OnBorderMouserUp"));
}

void UTitleBar::CloseWindow()
{
	UObject* ParentWidget = GetOuter()->GetOuter();
	if (ParentWidget->IsA(USkillWindow::StaticClass()))
	{
		m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_SkillWindow);
	}
	else if (ParentWidget->IsA(UStatusWindow::StaticClass()))
	{
		m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_StatusWindow);
	}
	else if (ParentWidget->IsA(UInventory::StaticClass()))
	{
		m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_Inventory);
	}
	else if (ParentWidget->IsA(UQuestWindow::StaticClass()))
	{
		m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestWindow);
	}
}

void UTitleBar::UpdateWindowLocation()
{
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	UUserWidget* ParentWidget = Cast<UUserWidget>(GetOuter()->GetOuter());
	UWidgetLayoutLibrary::SlotAsCanvasSlot(ParentWidget)->SetPosition(MousePosition-m_ClickLocationDiff);
}

void UTitleBar::UpdateWindowLocationStop()
{
	GetWorld()->GetTimerManager().ClearTimer(m_UpdateTimerHandle);
}

void UTitleBar::OnBorderMouserDown()
{
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	UUserWidget* ParentWidget = Cast<UUserWidget>(GetOuter()->GetOuter());
	FVector2D WidgetPosition = UWidgetLayoutLibrary::SlotAsCanvasSlot(ParentWidget)->GetPosition();
	m_ClickLocationDiff = MousePosition - WidgetPosition;
	GetWorld()->GetTimerManager().SetTimer(m_UpdateTimerHandle, this, &UTitleBar::UpdateWindowLocation, 0.01f, true);
}

void UTitleBar::OnBorderMouserUp()
{
	UpdateWindowLocationStop();
}
