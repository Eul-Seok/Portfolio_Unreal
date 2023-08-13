// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"


UCLASS()
class TESTCPP1_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPauseMenu(const FObjectInitializer& ObjectInitializer);

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
		class UButton* Button_GameMethod;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Quit;
	UPROPERTY(meta = (BindWidget))
		class UOptionWindow* W_OptionWindow;
	UPROPERTY(meta = (BindWidget))
		class UGameMethodWindow* W_GameMethodWindow;

protected:
	class AGameMgr* m_pGameMgr;

protected:
	UFUNCTION()
		void GameStart();
	UFUNCTION()
		void OpenPanelOption();
	UFUNCTION()
		void GameQuit();

public:
	UFUNCTION()
	void F_OpenPanelGameMethod();
	void F_DisplayMenu();

};
