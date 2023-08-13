// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"


UCLASS()
class TESTCPP1_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Menu;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Start;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Option;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Credits;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Quit;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Credits;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_CloseCredits;
	UPROPERTY(meta = (BindWidget))
	class UOptionWindow* W_OptionWindow;


protected:
	UFUNCTION()
	void GameStart();
	UFUNCTION()
	void OpenPanelOption();
	UFUNCTION()
	void OpenPanelCredits();
	UFUNCTION()
	void ClosePanelCredits();
	UFUNCTION()
	void GameQuit();

public:
	void F_DisplayMenu();

};
