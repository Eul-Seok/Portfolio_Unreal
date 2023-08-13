// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BuffIcon.h"
#include "Skill/Skill_Buff.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

UBuffIcon::UBuffIcon(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UBuffIcon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (m_pBuffTimerHandle->IsValid())
	{
		float ElapsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(*m_pBuffTimerHandle);
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(*m_pBuffTimerHandle);
		float InPercent = UKismetMathLibrary::NormalizeToRange(RemainingTime, 0.0f, ElapsedTime + RemainingTime);
		ProgressBar_BuffTimer->SetPercent(1 - InPercent);
	}
}
void UBuffIcon::CallClearBuffIcon()
{
	RemoveFromParent();
}

void UBuffIcon::F_SetBuffSkillInfo(ASkill_Buff* BuffSkill)
{
	Image_BuffIcon->SetBrushFromTexture(BuffSkill->F_GetSkillData()->m_SkillImage);
	m_pBuffTimerHandle = BuffSkill->F_GetBuffTimerHandle();
	BuffSkill->DELE_BuffRemoved.AddUFunction(this, FName("CallClearBuffIcon"));
}


