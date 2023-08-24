// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetBarMini.generated.h"

/**
 * 
 */
UCLASS()
class TESTCPP1_API UTargetBarMini : public UUserWidget
{
	GENERATED_BODY()

public:
	UTargetBarMini(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TargetNameText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* TargetHealthBar;

protected:
	class AMonster* m_Monster;
	class AMyPlayerController* m_PlayerController;

protected:
	UFUNCTION()
	void CallDisplayTargetName();
	UFUNCTION()
	void CallHiddenTargetName();
	UFUNCTION()
	void CallUpdateTargetHealthBar();

public:
	void F_SetTargetInfo(AActor* Target);
	void F_DisplayTargetNameText(bool bDisplay);
	void F_DisplayTargetHealthBar(bool bDisplay);

public:
	FORCEINLINE UTextBlock* F_GetTargetNameText() { return TargetNameText; }
	FORCEINLINE UProgressBar* F_GetTargetHealthBar() { return TargetHealthBar; }

};
