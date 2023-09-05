// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionBar.generated.h"


UCLASS()
class TESTCPP1_API UActionBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UActionBar(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LevelText;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ManaBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ExpBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HealthText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ManaText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ExpText;

protected:
	class UPlayerStatusComponent* m_PlayerStatusComponent;

protected:
	UFUNCTION()
	void CallUpdateStatusBar();

};
