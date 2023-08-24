// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleBar.generated.h"

UCLASS()
class TESTCPP1_API UTitleBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UTitleBar(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canvas_Panel;
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_WindowBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Close;

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	FTimerHandle m_UpdateTimerHandle;
	FVector2D m_ClickLocationDiff;
protected:
	UFUNCTION()
	void CloseWindow();
	void UpdateWindowLocation();
	void UpdateWindowLocationStop();

public:
	FORCEINLINE UTextBlock* F_GetTitleTextBlock() { return Title; }

public:
	UFUNCTION()
	void OnBorderMouserDown();
	UFUNCTION()
	void OnBorderMouserUp();

};
