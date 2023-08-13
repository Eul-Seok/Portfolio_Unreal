// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skill/SkillData.h"
#include "SkillToolTip.generated.h"

UCLASS()
class TESTCPP1_API USkillToolTip : public UUserWidget
{
	GENERATED_BODY()

public:
	USkillToolTip(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_SkillIcon;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_AffectValue;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Cost;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CooldownTime;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Description;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillLevel;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillPoint;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Restriction;

protected:
	FSkillData* m_pSkillData;
	uint8 m_CurrentSkillLevel;

public:
	void F_UpdateToolTip();
	void F_UpdateSkillAffectValue();
	void F_SetSkillData(FSkillData* SkillData);
	void F_SetCurrentSkillLevel(uint8 CurrentSkillLevel);
	void F_RemoveRestrictionText();
};
