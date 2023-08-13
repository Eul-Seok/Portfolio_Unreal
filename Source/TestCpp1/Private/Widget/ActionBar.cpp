// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ActionBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/PlayerStatusComponent.h"

UActionBar::UActionBar(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UActionBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ATestCpp1Character* Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		m_PlayerStatusComponent = Player->F_GetPlayerStatusComponent();
		m_PlayerStatusComponent->DELE_RequestUpdateStatusBar.AddUFunction(this, FName("CallUpdateStatusBar"));
		m_PlayerStatusComponent->DELE_RequestUpdateStatusBar.Broadcast();
	}
}

void UActionBar::CallUpdateStatusBar()
{
	HealthBar->SetPercent(m_PlayerStatusComponent->F_GetHealthNormalized());
	HealthText->SetText((FText::FromString(FString::Printf(TEXT("%.1f / %.1f"), m_PlayerStatusComponent->F_GetHealthCurrent(), m_PlayerStatusComponent->F_GetHealthMax()))));
	ManaBar->SetPercent(m_PlayerStatusComponent->F_GetManaNormalized());
	ManaText->SetText((FText::FromString(FString::Printf(TEXT("%.1f / %.1f"), m_PlayerStatusComponent->F_GetManaCurrent(), m_PlayerStatusComponent->F_GetManaMax()))));
	
	LevelText->SetText((FText::FromString(FString::Printf(TEXT("Level: %d"), m_PlayerStatusComponent->F_GetLevel()))));
	ExpBar->SetPercent(m_PlayerStatusComponent->F_GetExpNormalized());
	ExpText->SetText((FText::FromString(FString::Printf(TEXT("%.1f / %.1f"), m_PlayerStatusComponent->F_GetExpCurrent(), m_PlayerStatusComponent->F_GetExpMax()))));
}
