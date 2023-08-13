// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainMenu.h"
#include "Widget/OptionWindow.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"



UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Button_Start->OnClicked.AddDynamic(this, &UMainMenu::GameStart);
	Button_Quit->OnClicked.AddDynamic(this, &UMainMenu::GameQuit);

	Button_Option->OnClicked.AddDynamic(this, &UMainMenu::OpenPanelOption);

	Button_Credits->OnClicked.AddDynamic(this, &UMainMenu::OpenPanelCredits);
	Button_CloseCredits->OnClicked.AddDynamic(this, &UMainMenu::ClosePanelCredits);
}

void UMainMenu::GameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Map_Game"));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UMainMenu::OpenPanelOption()
{
	Panel_Menu->SetVisibility(ESlateVisibility::Hidden);
	W_OptionWindow->F_DisplayOptionWindow();
}

void UMainMenu::OpenPanelCredits()
{
	Panel_Menu->SetVisibility(ESlateVisibility::Hidden);
	Panel_Credits->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UMainMenu::ClosePanelCredits()
{
	Panel_Menu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Panel_Credits->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::GameQuit()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
}

void UMainMenu::F_DisplayMenu()
{
	Panel_Menu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
