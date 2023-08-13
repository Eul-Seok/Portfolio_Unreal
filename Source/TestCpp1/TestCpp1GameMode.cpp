// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestCpp1GameMode.h"
#include "Player/TestCpp1Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Widget/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

ATestCpp1GameMode::ATestCpp1GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATestCpp1GameMode::BeginPlay()
{
	Super::BeginPlay();
	if (W_StartingMainMenuWidgetClass)
	{
		CreateWidget<UMainMenu>(GetWorld(), W_StartingMainMenuWidgetClass)->AddToViewport();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
		PlayerController->SetShowMouseCursor(true);
	}
}
