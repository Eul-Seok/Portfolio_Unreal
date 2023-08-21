// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffIcon.generated.h"

class ASkill_Buff;

UCLASS()
class TESTCPP1_API UBuffIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	UBuffIcon(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_BuffIcon;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_BuffTimer;

protected:
	FTimerHandle* m_pBuffTimerHandle;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UFUNCTION()
	void CallClearBuffIcon();

public:
	void F_SetBuffSkillInfo(ASkill_Buff* BuffSkill);

};

