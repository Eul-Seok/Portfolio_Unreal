// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PauseMenu.h"
#include "Widget/OptionWindow.h"
#include "Widget/GameMethodWindow.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"

UPauseMenu::UPauseMenu(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UPauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	Button_Start->OnClicked.AddDynamic(this, &UPauseMenu::GameStart);
	Button_Option->OnClicked.AddDynamic(this, &UPauseMenu::OpenPanelOption);
	Button_GameMethod->OnClicked.AddDynamic(this, &UPauseMenu::F_OpenPanelGameMethod);
	Button_Quit->OnClicked.AddDynamic(this, &UPauseMenu::GameQuit);
}

void UPauseMenu::GameStart()
{
	m_pGameMgr->F_GetWidgetMgr()->F_TogglePauseMenu();
}

void UPauseMenu::OpenPanelOption()
{
	Panel_Menu->SetVisibility(ESlateVisibility::Hidden);
	W_OptionWindow->F_DisplayOptionWindow();
}

void UPauseMenu::F_OpenPanelGameMethod()
{
	Panel_Menu->SetVisibility(ESlateVisibility::Hidden);
	W_GameMethodWindow->F_DisplayGameMethodWindow();
}

void UPauseMenu::GameQuit()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
}

void UPauseMenu::F_DisplayMenu()
{
	Panel_Menu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
