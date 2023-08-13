// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWindow.generated.h"


UCLASS()
class TESTCPP1_API UStatusWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UStatusWindow(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTitleBar* W_TitleBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_HP;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MP;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_StrikingPower;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_DefensivePower;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Strength;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Agility;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Constitution;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Intelligence;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_RemainingStatusPoint;
		
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_StrengthUP;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_AgilityUP;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_ConstitutionUP;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_IntelligenceUP;

protected:
	UPROPERTY()
	class UPlayerStatusComponent* m_PlayerStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float m_fStrikingPower;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float m_fDefensivePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 m_nStrength;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 m_nAgility;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 m_nConstitution;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 m_nIntelligence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 m_nStatusPoint;

protected:
	void ButtonBinding();
	UFUNCTION()
	void UpdateStatus();
	UFUNCTION()
	void CallDisplayStatusUpButton();
	UFUNCTION()
	void CallUpdateStatusBar();
	UFUNCTION()
	void CallUpdatePower();
	UFUNCTION()
	void UpStrength();
	UFUNCTION()
	void UpAgility();
	UFUNCTION()
	void UpConstitution();
	UFUNCTION()
	void UpIntelligence();
	
};
