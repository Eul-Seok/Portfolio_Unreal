// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StatusWindow.h"
#include "Widget/TitleBar.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

UStatusWindow::UStatusWindow(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{

}

void UStatusWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ATestCpp1Character* Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	m_PlayerStatusComponent = Player->F_GetPlayerStatusComponent();
	if (Player)
	{
		m_PlayerStatusComponent->DELE_RequestUpdateStatusBar.AddUFunction(this, FName("CallUpdateStatusBar"));
		m_PlayerStatusComponent->DELE_RequestUpdateStatusBar.Broadcast();
		m_PlayerStatusComponent->DELE_RequestUpdatePower.BindUFunction(this, FName("CallUpdatePower"));
		m_PlayerStatusComponent->DELE_RequestUpdatePower.ExecuteIfBound();
		m_PlayerStatusComponent->DELE_LevelUp.AddUFunction(this, FName("CallDisplayStatusUpButton"));
		UpdateStatus();
		ButtonBinding();
	}

	W_TitleBar->F_GetTitleTextBlock()->SetText(FText::FromString(FString::Printf(TEXT("상태창"))));
}

void UStatusWindow::CallUpdateStatusBar()
{
	Text_HP->SetText((FText::FromString(FString::Printf(TEXT("%.1f / %.1f"), m_PlayerStatusComponent->F_GetHealthCurrent(), m_PlayerStatusComponent->F_GetHealthMax()))));
	Text_MP->SetText((FText::FromString(FString::Printf(TEXT("%.1f / %.1f"), m_PlayerStatusComponent->F_GetManaCurrent(), m_PlayerStatusComponent->F_GetManaMax()))));
}

void UStatusWindow::CallUpdatePower()
{
	float fAttackStrikingPower = m_PlayerStatusComponent->F_GetAttackStrikingPower();
	float fBuffAppliedStrikingPower = m_PlayerStatusComponent->F_GetBuffAppliedStrikingPower();
	float fBuffAppliedDefensivePower = m_PlayerStatusComponent->F_GetBuffAppliedDefensivePower();
	if (fAttackStrikingPower != 0.0f)
	{
		Text_StrikingPower->SetText((FText::FromString(FString::Printf(TEXT("%.1f"), fAttackStrikingPower))));
	}
	else
	{
		if (fBuffAppliedStrikingPower != 0.0f)
		{
			Text_StrikingPower->SetText((FText::FromString(FString::Printf(TEXT("%.1f"), fBuffAppliedStrikingPower))));
		}
		else
		{
			Text_StrikingPower->SetText((FText::FromString(FString::Printf(TEXT("%.1f"), m_PlayerStatusComponent->F_GetStrikingPower()))));
		}
	}
	if (fBuffAppliedDefensivePower != 0.0f)
	{
		Text_DefensivePower->SetText((FText::FromString(FString::Printf(TEXT("%.1f"), fBuffAppliedDefensivePower))));
	}
	else
	{
		Text_DefensivePower->SetText((FText::FromString(FString::Printf(TEXT("%.1f"), m_PlayerStatusComponent->F_GetDefensivePower()))));
	}
}

void UStatusWindow::UpdateStatus()
{
	m_nStrength = m_PlayerStatusComponent->F_GetStrength();
	m_nAgility = m_PlayerStatusComponent->F_GetAgility();
	m_nConstitution = m_PlayerStatusComponent->F_GetConstitution();
	m_nIntelligence = m_PlayerStatusComponent->F_GetIntelligence();
	m_nStatusPoint = m_PlayerStatusComponent->F_GetStatusPoint();

	Text_Strength->SetText((FText::FromString(FString::Printf(TEXT("%d"), m_nStrength))));
	Text_Agility->SetText((FText::FromString(FString::Printf(TEXT("%d"), m_nAgility))));
	Text_Constitution->SetText((FText::FromString(FString::Printf(TEXT("%d"), m_nConstitution))));
	Text_Intelligence->SetText((FText::FromString(FString::Printf(TEXT("%d"), m_nIntelligence))));
	Text_RemainingStatusPoint->SetText((FText::FromString(FString::Printf(TEXT("%d"), m_nStatusPoint))));
	
	if (m_nStatusPoint == 0)
	{
		Button_StrengthUP->SetVisibility(ESlateVisibility::Hidden);
		Button_AgilityUP->SetVisibility(ESlateVisibility::Hidden);
		Button_ConstitutionUP->SetVisibility(ESlateVisibility::Hidden);
		Button_IntelligenceUP->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UStatusWindow::CallDisplayStatusUpButton()
{
	Button_StrengthUP->SetVisibility(ESlateVisibility::Visible);
	Button_AgilityUP->SetVisibility(ESlateVisibility::Visible);
	Button_ConstitutionUP->SetVisibility(ESlateVisibility::Visible);
	Button_IntelligenceUP->SetVisibility(ESlateVisibility::Visible);
	m_nStatusPoint = m_PlayerStatusComponent->F_GetStatusPoint();
	Text_RemainingStatusPoint->SetText((FText::FromString(FString::Printf(TEXT("%d"), m_nStatusPoint))));
}

void UStatusWindow::ButtonBinding()
{
	Button_StrengthUP->OnClicked.AddDynamic(this, &UStatusWindow::UpStrength);
	Button_AgilityUP->OnClicked.AddDynamic(this, &UStatusWindow::UpAgility);
	Button_ConstitutionUP->OnClicked.AddDynamic(this, &UStatusWindow::UpConstitution);
	Button_IntelligenceUP->OnClicked.AddDynamic(this, &UStatusWindow::UpIntelligence);
}

void UStatusWindow::UpStrength()
{
	m_PlayerStatusComponent->F_StatusUpApply(EPlayerStatus::E_Strength);
	UpdateStatus();
}

void UStatusWindow::UpAgility()
{
	m_PlayerStatusComponent->F_StatusUpApply(EPlayerStatus::E_Agility);
	UpdateStatus();
}

void UStatusWindow::UpConstitution()
{
	m_PlayerStatusComponent->F_StatusUpApply(EPlayerStatus::E_Constitution);
	UpdateStatus();
}

void UStatusWindow::UpIntelligence()
{
	m_PlayerStatusComponent->F_StatusUpApply(EPlayerStatus::E_Intelligence);
	UpdateStatus();
}
