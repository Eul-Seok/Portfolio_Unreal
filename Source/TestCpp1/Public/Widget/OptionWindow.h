// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWindow.generated.h"

UCLASS()
class TESTCPP1_API UOptionWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UOptionWindow(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* Panel_Option;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CloseOption;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_FullScreenMode;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_WindowedMode;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_720x480;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_1280x720;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_1920x1080;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_2560x1440;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_LowAA;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_MediumAA;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_HighAA;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_UltraAA;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_LowShadow;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_MediumShadow;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_HighShadow;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_UltraShadow;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_LowTexture;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_MediumTexture;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_HighTexture;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_UltraTexture;
	
protected:
	UFUNCTION()
		void HiddenOptionWindow();

	UFUNCTION()
		void OnButtonClicked_FullScreenMode();
	UFUNCTION()
		void OnButtonClicked_WindowedMode();

	UFUNCTION()
		void OnButtonClicked_720x480();
	UFUNCTION()
		void OnButtonClicked_1280x720();
	UFUNCTION()
		void OnButtonClicked_1920x1080();
	UFUNCTION()
		void OnButtonClicked_2560x1440();

	UFUNCTION()
		void OnButtonClicked_LowAA();
	UFUNCTION()
		void OnButtonClicked_MediumAA();
	UFUNCTION()
		void OnButtonClicked_HighAA();
	UFUNCTION()
		void OnButtonClicked_UltraAA();

	UFUNCTION()
		void OnButtonClicked_LowShadow();
	UFUNCTION()
		void OnButtonClicked_MediumShadow();
	UFUNCTION()
		void OnButtonClicked_HighShadow();
	UFUNCTION()
		void OnButtonClicked_UltraShadow();

	UFUNCTION()
		void OnButtonClicked_LowTexture();
	UFUNCTION()
		void OnButtonClicked_MediumTexture();
	UFUNCTION()
		void OnButtonClicked_HighTexture();
	UFUNCTION()
		void OnButtonClicked_UltraTexture();

public:
	void F_DisplayOptionWindow();

};
