// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TargetBarMini.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerController.h"
#include "Monster/Monster.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UTargetBarMini::UTargetBarMini(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UTargetBarMini::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_PlayerController->DELE_TargetChange.AddUFunction(this, FName("CallDisplayTargetName"));
	m_PlayerController->DELE_TargetCancled.AddUFunction(this, FName("CallHiddenTargetName"));
}

void UTargetBarMini::CallDisplayTargetName()
{
	AMonster* CurrentTarget = m_PlayerController->F_GetCurrentTarget();
	if (m_Monster == CurrentTarget)
	{
		F_DisplayTargetNameText(true);
	}
	else
	{
		CallHiddenTargetName();
	}
}

void UTargetBarMini::CallHiddenTargetName()
{
	F_DisplayTargetNameText(false);
}

void UTargetBarMini::CallUpdateTargetHealthBar()
{
	TargetHealthBar->SetPercent(m_Monster->F_GetMonsterStatusComponent()->F_GetHealthNormalized());
}

void UTargetBarMini::F_SetTargetInfo(AActor* Target)
{
	m_Monster = Cast<AMonster>(Target);
	TargetNameText->SetText(*m_Monster->F_GetMonsterName());
	TargetHealthBar->SetPercent(m_Monster->F_GetMonsterStatusComponent()->F_GetHealthNormalized());
	m_Monster->DELE_TargetStatusBarMiniUpdate.BindUFunction(this, FName("CallUpdateTargetHealthBar"));
}

void UTargetBarMini::F_DisplayTargetNameText(bool bDisplay)
{
	if (bDisplay)
	{
		TargetNameText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		TargetNameText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTargetBarMini::F_DisplayTargetHealthBar(bool bDisplay)
{
	if (bDisplay)
	{
		TargetHealthBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		TargetHealthBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

UTextBlock* UTargetBarMini::F_GetTargetNameText()
{
	return TargetNameText;
}

UProgressBar* UTargetBarMini::F_GetTargetHealthBar()
{
	return TargetHealthBar;
}
