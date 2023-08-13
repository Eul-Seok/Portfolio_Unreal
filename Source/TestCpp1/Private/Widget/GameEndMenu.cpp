// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameEndMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Player/TestCpp1Character.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"

UGameEndMenu::UGameEndMenu(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UGameEndMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	Button_Revival->OnClicked.AddDynamic(this, &UGameEndMenu::Revival);
	Button_Quit->OnClicked.AddDynamic(this, &UGameEndMenu::GameQuit);
	Button_Play->OnClicked.AddDynamic(this, &UGameEndMenu::GamePlay);
	Button_Quit2->OnClicked.AddDynamic(this, &UGameEndMenu::GameQuit);
}

void UGameEndMenu::F_DisplayRevivalMenu()
{
	Panel_RevivalMenu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Panel_GameClearMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UGameEndMenu::F_DisplayGameClearMenu()
{
	Panel_RevivalMenu->SetVisibility(ESlateVisibility::Hidden);
	Panel_GameClearMenu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UGameEndMenu::GamePlay()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleGameClearMenu();
}

void UGameEndMenu::Revival()
{
	ATestCpp1Character* Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->F_Revival();
}

void UGameEndMenu::GameQuit()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
}
