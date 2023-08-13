// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CastBar.generated.h"

DECLARE_DELEGATE(FDele_Single);

UCLASS()
class TESTCPP1_API UCastBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCastBar(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CastBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillName;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Interrupted;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Reset;

public:
	class ASkill_Base* m_Skill;
	UPROPERTY()
	FTimerHandle m_CastTimer;
	UPROPERTY()
	FWidgetAnimationDynamicEvent m_InterruptedAnimationEvent;

public:
	void CompletedCast();
	UFUNCTION()
	void InterruptedCast();
	UFUNCTION()
	void AnimationFinished();

public:
	void F_StartCast();
	void F_SetSkill(ASkill_Base* Skill);

public:
	FDele_Single DELE_CompletedCast;
	
};
