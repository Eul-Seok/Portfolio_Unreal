// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TargetBar.h"
#include "Widget/BuffPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerController.h"
#include "Monster/Monster.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "ActorComponent/MonsterStatusComponent.h"
#include "Skill/Skill_Buff.h"

UTargetBar::UTargetBar(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UTargetBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_PlayerController->DELE_TargetChange.AddUFunction(this, FName("CallUpdateTargetStatusBar"));
	m_PlayerController->DELE_TargetCancled.AddUFunction(this, FName("CallHiddenTargetStatusBar"));
}

void UTargetBar::CallUpdateTargetStatusBar()
{
	if (m_Target)
	{
		TargetNameText->SetText(*m_Target->F_GetMonsterName());
		TargetHealthBar->SetPercent(m_MonsterStatusComponent->F_GetHealthNormalized());
		HealthText->SetText((FText::FromString(FString::Printf(TEXT("%.1f / %.1f"), m_MonsterStatusComponent->F_GetHealthCurrent(), m_MonsterStatusComponent->F_GetHealthMax()))));
	}
}

void UTargetBar::CallHiddenTargetStatusBar()
{
	m_PlayerController->F_TargetClear();
	SetVisibility(ESlateVisibility::Hidden);
}

void UTargetBar::F_SetTargetInfo(AMonster* Monster)
{
	m_Target = Monster;
	m_MonsterStatusComponent = m_Target->F_GetMonsterStatusComponent();
	if (!m_Target->DELE_TargetStatusBarUpdate.IsBound())
	{
		m_Target->DELE_TargetStatusBarUpdate.BindUFunction(this, FName("CallUpdateTargetStatusBar"));
	}
	F_UpdateBuffIcon();
	SetVisibility(ESlateVisibility::Visible);
}

void UTargetBar::F_UpdateBuffIcon()
{
	W_BuffPanel->F_ClearPanel();
	TArray<AActor*> arAttachedActor{};
	m_Target->GetAttachedActors(arAttachedActor);
	for (uint8 i = 0; i < arAttachedActor.Num(); i++)
	{
		ASkill_Buff* BuffSkill = Cast<ASkill_Buff>(arAttachedActor[i]);
		if (BuffSkill)
		{
			W_BuffPanel->F_AddBuff(BuffSkill);
		}
	}
}
