// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageIndicator.generated.h"

UCLASS()
class TESTCPP1_API UDamageIndicator : public UUserWidget
{
	GENERATED_BODY()

public:
	UDamageIndicator(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Damage;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Fade;
	
	UPROPERTY()
	FWidgetAnimationDynamicEvent m_InterruptedAnimationEvent;

protected:
	float m_fDamage;

public:
	void F_SetDamage(float fDamage);
};
