// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndMenu.generated.h"

UCLASS()
class TESTCPP1_API UGameEndMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameEndMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* Panel_RevivalMenu;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Revival;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Quit;
	
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* Panel_GameClearMenu;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Play;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Quit2;

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;

protected:
	UFUNCTION()
	void GamePlay();
	UFUNCTION()
	void Revival();
	UFUNCTION()
	void GameQuit();

public:
	void F_DisplayRevivalMenu();
	void F_DisplayGameClearMenu();
};
