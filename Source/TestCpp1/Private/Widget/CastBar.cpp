// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CastBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Player/MyPlayerController.h"
#include "Skill/Skill_Base.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UCastBar::UCastBar(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UCastBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->DELE_InterruptCasting.BindUFunction(this, FName("InterruptedCast"));
		m_InterruptedAnimationEvent.BindDynamic(this, &UCastBar::AnimationFinished);
		BindToAnimationFinished(Interrupted, m_InterruptedAnimationEvent);
	}
}

void UCastBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (IsVisible()&& m_CastTimer.IsValid())
	{
		float ElapsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(m_CastTimer);
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(m_CastTimer);
		float InPercent = UKismetMathLibrary::NormalizeToRange(ElapsedTime, 0.0f, ElapsedTime + RemainingTime);
		CastBar->SetPercent(InPercent);
	}
}

void UCastBar::CompletedCast()
{
	DELE_CompletedCast.ExecuteIfBound();
	SetVisibility(ESlateVisibility::Hidden);
}

void UCastBar::InterruptedCast()
{
	if (IsValid(m_Skill))
	{
		if (IsVisible())
		{
			m_Skill->F_InterruptedCast();
			PlayAnimation(Interrupted);
			Text_SkillName->SetText(FText::FromString(FString::Printf(TEXT("캐스팅이 방해받았습니다"))));
			GetWorld()->GetTimerManager().ClearTimer(m_CastTimer);
		}
	}
}

void UCastBar::AnimationFinished()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UCastBar::F_StartCast()
{
	StopAnimation(Interrupted);
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(Reset);
	Text_SkillName->SetText(FText::FromString(FString::Printf(TEXT("'%s' 스킬 캐스팅"), *m_Skill->F_GetSkillData()->m_SkillName.ToString())));
	GetWorld()->GetTimerManager().SetTimer(m_CastTimer, this, &UCastBar::CompletedCast, m_Skill->F_GetCastTime(), false);
}

void UCastBar::F_SetSkill(ASkill_Base* Skill)
{
	m_Skill = Skill;
}
