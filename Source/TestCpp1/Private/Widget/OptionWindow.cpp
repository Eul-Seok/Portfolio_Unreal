// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OptionWindow.h"
#include "Widget/MainMenu.h"
#include "Widget/PauseMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"



UOptionWindow::UOptionWindow(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UOptionWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_CloseOption->OnClicked.AddDynamic(this, &UOptionWindow::HiddenOptionWindow);
	Button_FullScreenMode->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_FullScreenMode);
	Button_WindowedMode->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_WindowedMode);
	Button_720x480->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_720x480);
	Button_1280x720->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_1280x720);
	Button_1920x1080->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_1920x1080);
	Button_2560x1440->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_2560x1440);
	Button_LowAA->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_LowAA);
	Button_MediumAA->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_MediumAA);
	Button_HighAA->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_HighAA);
	Button_UltraAA->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_UltraAA);
	Button_LowShadow->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_LowShadow);
	Button_MediumShadow->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_MediumShadow);
	Button_HighShadow->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_HighShadow);
	Button_UltraShadow->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_UltraShadow);
	Button_LowTexture->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_LowTexture);
	Button_MediumTexture->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_MediumTexture);
	Button_HighTexture->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_HighTexture);
	Button_UltraTexture->OnClicked.AddDynamic(this, &UOptionWindow::OnButtonClicked_UltraTexture);

}

void UOptionWindow::HiddenOptionWindow()
{
	Panel_Option->SetVisibility(ESlateVisibility::Hidden);
	UMainMenu* MainMenu = Cast<UMainMenu>(GetOuter()->GetOuter());
	if (MainMenu)
	{
		MainMenu->F_DisplayMenu();
	}
	UPauseMenu* PauseMenu = Cast<UPauseMenu>(GetOuter()->GetOuter());
	if (PauseMenu)
	{
		PauseMenu->F_DisplayMenu();
	}
}

void UOptionWindow::OnButtonClicked_FullScreenMode()
{
	UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen);
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);
	Button_FullScreenMode->SetIsEnabled(false);
	Button_WindowedMode->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_WindowedMode()
{
	UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);
	Button_FullScreenMode->SetIsEnabled(true);
	Button_WindowedMode->SetIsEnabled(false);
}

void UOptionWindow::OnButtonClicked_720x480()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.setres 720x480");
	Button_720x480->SetIsEnabled(false);
	Button_1280x720->SetIsEnabled(true);
	Button_1920x1080->SetIsEnabled(true);
	Button_2560x1440->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_1280x720()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.setres 1280x720");
	Button_720x480->SetIsEnabled(true);
	Button_1280x720->SetIsEnabled(false);
	Button_1920x1080->SetIsEnabled(true);
	Button_2560x1440->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_1920x1080()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.setres 1920x1080");
	Button_720x480->SetIsEnabled(true);
	Button_1280x720->SetIsEnabled(true);
	Button_1920x1080->SetIsEnabled(false);
	Button_2560x1440->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_2560x1440()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.setres 2560x1440");
	Button_720x480->SetIsEnabled(true);
	Button_1280x720->SetIsEnabled(true);
	Button_1920x1080->SetIsEnabled(true);
	Button_2560x1440->SetIsEnabled(false);
}

void UOptionWindow::OnButtonClicked_LowAA()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.PostProcessAAQuality 0");
	Button_LowAA->SetIsEnabled(false);
	Button_MediumAA->SetIsEnabled(true);
	Button_HighAA->SetIsEnabled(true);
	Button_UltraAA->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_MediumAA()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.PostProcessAAQuality 2");
	Button_LowAA->SetIsEnabled(true);
	Button_MediumAA->SetIsEnabled(false);
	Button_HighAA->SetIsEnabled(true);
	Button_UltraAA->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_HighAA()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.PostProcessAAQuality 4");
	Button_LowAA->SetIsEnabled(true);
	Button_MediumAA->SetIsEnabled(true);
	Button_HighAA->SetIsEnabled(false);
	Button_UltraAA->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_UltraAA()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.PostProcessAAQuality 6");
	Button_LowAA->SetIsEnabled(true);
	Button_MediumAA->SetIsEnabled(true);
	Button_HighAA->SetIsEnabled(true);
	Button_UltraAA->SetIsEnabled(false);
}

void UOptionWindow::OnButtonClicked_LowShadow()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.ShadowQuality 0");
	Button_LowShadow->SetIsEnabled(false);
	Button_MediumShadow->SetIsEnabled(true);
	Button_HighShadow->SetIsEnabled(true);
	Button_UltraShadow->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_MediumShadow()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.ShadowQuality 1");
	Button_LowShadow->SetIsEnabled(true);
	Button_MediumShadow->SetIsEnabled(false);
	Button_HighShadow->SetIsEnabled(true);
	Button_UltraShadow->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_HighShadow()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.ShadowQuality 2");
	Button_LowShadow->SetIsEnabled(true);
	Button_MediumShadow->SetIsEnabled(true);
	Button_HighShadow->SetIsEnabled(false);
	Button_UltraShadow->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_UltraShadow()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.ShadowQuality 3");
	Button_LowShadow->SetIsEnabled(true);
	Button_MediumShadow->SetIsEnabled(true);
	Button_HighShadow->SetIsEnabled(true);
	Button_UltraShadow->SetIsEnabled(false);
}

void UOptionWindow::OnButtonClicked_LowTexture()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.TextureQuality 0");
	Button_LowTexture->SetIsEnabled(false);
	Button_MediumTexture->SetIsEnabled(true);
	Button_HighTexture->SetIsEnabled(true);
	Button_UltraTexture->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_MediumTexture()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.TextureQuality 1");
	Button_LowTexture->SetIsEnabled(true);
	Button_MediumTexture->SetIsEnabled(false);
	Button_HighTexture->SetIsEnabled(true);
	Button_UltraTexture->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_HighTexture()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.TextureQuality 2");
	Button_LowTexture->SetIsEnabled(true);
	Button_MediumTexture->SetIsEnabled(true);
	Button_HighTexture->SetIsEnabled(false);
	Button_UltraTexture->SetIsEnabled(true);
}

void UOptionWindow::OnButtonClicked_UltraTexture()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "sg.TextureQuality 3");
	Button_LowTexture->SetIsEnabled(true);
	Button_MediumTexture->SetIsEnabled(true);
	Button_HighTexture->SetIsEnabled(true);
	Button_UltraTexture->SetIsEnabled(false);
}

void UOptionWindow::F_DisplayOptionWindow()
{
	Panel_Option->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

