// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetBar.generated.h"

UCLASS()
class TESTCPP1_API UTargetBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UTargetBar(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TargetNameText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* TargetHealthBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;
	UPROPERTY(meta = (BindWidget))
	class UBuffPanel* W_BuffPanel;

protected:
	UPROPERTY()
	class AMyPlayerController* m_PlayerController;
	UPROPERTY()
	class AMonster* m_Target;
	UPROPERTY()
	class UMonsterStatusComponent* m_MonsterStatusComponent;

protected:
	UFUNCTION()
	void CallUpdateTargetStatusBar();
	UFUNCTION()
	void CallHiddenTargetStatusBar();
	

public:
	void F_SetTargetInfo(AMonster* Monster);
	void F_UpdateBuffIcon();
};
