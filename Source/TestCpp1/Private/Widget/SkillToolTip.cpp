// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ActorComponent/PlayerSkillsComponent.h"
#include "Player/TestCpp1Character.h"

USkillToolTip::USkillToolTip(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void USkillToolTip::F_UpdateToolTip()
{
	Text_SkillLevel->SetText(FText::FromString(FString::Printf(TEXT("스킬 레벨: %d / %d"), m_CurrentSkillLevel ,m_pSkillData->m_MaxSkillLevel)));
	if (m_pSkillData->m_MaxSkillLevel > m_CurrentSkillLevel)
	{
		Text_SkillPoint->SetText(FText::FromString(FString::Printf(TEXT("필요 스킬 포인트: %d"), m_pSkillData->m_SkillPoint)));
	}
	else
	{
		Text_SkillPoint->SetText(FText::FromString(FString::Printf(TEXT(""))));
	}
	F_UpdateSkillAffectValue();
}

void USkillToolTip::F_UpdateSkillAffectValue()
{
	if (m_pSkillData->m_AffectValue > 0.0f)
	{
		uint8 nCurrentSkillLevel{};
		float fFinalAffectValue{};
		float fSkillIncrementValue = 0.1f;
		Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->F_GetPlayerSkillsComponent()->F_QuerySkill(m_pSkillData->m_SkillName, nCurrentSkillLevel);
		if (nCurrentSkillLevel == 0)
		{
			fFinalAffectValue = m_pSkillData->m_AffectValue;
		}
		else
		{
			fFinalAffectValue = (m_pSkillData->m_AffectValue + (fSkillIncrementValue * (float)(nCurrentSkillLevel - 1)));
		}
		Text_AffectValue->SetText(FText::FromString(FString::Printf(TEXT("데미지: 공격력 * %.1f"), fFinalAffectValue)));
		if (m_pSkillData->m_SkillWeaponType == ESkillWeaponType::E_Common)
		{
			Text_AffectValue->SetText(FText::FromString(FString::Printf(TEXT("해당 능력치 * %.1f"), fFinalAffectValue)));
		}
	}
	else
	{
		Text_AffectValue->SetText(FText::FromString(FString::Printf(TEXT("데미지: 공격력 * 횟수"))));
	}
}

void USkillToolTip::F_SetSkillData(FSkillData* SkillData)
{
	m_pSkillData = SkillData;
	if (m_pSkillData->m_SkillWeaponType == ESkillWeaponType::E_Default)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Image_SkillIcon->SetBrushFromTexture(m_pSkillData->m_SkillImage);
		Text_SkillName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *m_pSkillData->m_SkillName.ToString())));
		Text_Cost->SetText(FText::FromString(FString::Printf(TEXT("마나 소모: %.0f"), m_pSkillData->m_Cost)));
		Text_CooldownTime->SetText(FText::FromString(FString::Printf(TEXT("쿨타임: %.1f초"), m_pSkillData->m_CoolDownTime)));
		Text_Description->SetText(m_pSkillData->m_SkillDescription);
		if (m_pSkillData->m_PreRequisiteSkillName != FName())
		{
			Text_Restriction->SetText(FText::FromString(FString::Printf(TEXT("'%s'\n스킬 레벨 %d 이상 필요"), *m_pSkillData->m_PreRequisiteSkillName.ToString(), m_pSkillData->m_PreRequisiteSkillLevel)));
		}
		else
		{
			Text_Restriction->SetText(FText::FromString(FString::Printf(TEXT(""))));
		}
		F_UpdateToolTip();
	}
}

void USkillToolTip::F_SetCurrentSkillLevel(uint8 CurrentSkillLevel)
{
	m_CurrentSkillLevel = CurrentSkillLevel;
}

void USkillToolTip::F_RemoveRestrictionText()
{
	Text_Restriction->SetText(FText::FromString(FString::Printf(TEXT(""))));
}


