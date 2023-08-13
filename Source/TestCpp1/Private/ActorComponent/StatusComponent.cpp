// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/StatusComponent.h"
#include "Monster/Monster.h"
#include "Player/TestCpp1Character.h"

UStatusComponent::UStatusComponent():
	m_nLevel{}, m_fHealthMax {}, m_fHealthCurrent{}, m_fHealthNormalized{}, m_fManaMax{}, m_fManaCurrent{}, m_fManaNormalized{},
	m_fStrikingPower{}, m_fDefensivePower{}, m_fAttackStrikingPower{}, m_fBuffAppliedStrikingPower{}, m_fBuffAppliedDefensivePower{}
{
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	m_fHealthNormalized = UKismetMathLibrary::NormalizeToRange(m_fHealthCurrent, 0.0f, m_fHealthMax);
	m_fManaNormalized = UKismetMathLibrary::NormalizeToRange(m_fManaCurrent, 0.0f, m_fManaMax);
}

void UStatusComponent::HealthRegenTick()
{
}

void UStatusComponent::ManaRegenTick()
{	
}

float UStatusComponent::CalculateChangeValue(float fStatusValue, float fDeltaValue, EOperatorType eOperator)
{
	if (eOperator == EOperatorType::E_Plus)
	{
		fStatusValue += fDeltaValue;
	}
	else if (eOperator == EOperatorType::E_Minus)
	{
		fStatusValue -= fDeltaValue;
	}
	else if (eOperator == EOperatorType::E_Multiply)
	{
		fStatusValue *= fDeltaValue;
	}
	else if (eOperator == EOperatorType::E_Divide)
	{
		fStatusValue /= fDeltaValue;
	}
	return fStatusValue;
}

void UStatusComponent::F_ResetAttackStrikingPower()
{
	m_fAttackStrikingPower = 0.0f;
}

void UStatusComponent::F_ResetBuffAppliedStrikingPower()
{
	m_fBuffAppliedStrikingPower = 0.0f;
}

void UStatusComponent::F_ResetBuffAppliedDefensivePower()
{
	m_fBuffAppliedDefensivePower = 0.0f;
}

void UStatusComponent::F_AddHealth(float fValue)
{
	float NewHealth = m_fHealthCurrent + fValue;
	m_fHealthCurrent = UKismetMathLibrary::FClamp(NewHealth, 0.0f, m_fHealthMax);
	m_fHealthNormalized = UKismetMathLibrary::NormalizeToRange(m_fHealthCurrent, 0.0f, m_fHealthMax);
}

void UStatusComponent::F_AddMana(float fValue)
{
	float NewMana = m_fManaCurrent + fValue;
	m_fManaCurrent = UKismetMathLibrary::FClamp(NewMana, 0.0f, m_fManaMax);
	m_fManaNormalized = UKismetMathLibrary::NormalizeToRange(m_fManaCurrent, 0.0f, m_fManaMax);
}

void UStatusComponent::F_ReduceHealth(float fValue)
{
	float NewHealth = m_fHealthCurrent - fValue;
	m_fHealthCurrent = UKismetMathLibrary::FClamp(NewHealth, 0.0f, m_fHealthMax);
	m_fHealthNormalized = UKismetMathLibrary::NormalizeToRange(m_fHealthCurrent, 0.0f, m_fHealthMax);
}

void UStatusComponent::F_ReduceMana(float fValue)
{
	float NewMana = m_fManaCurrent - fValue;
	m_fManaCurrent = UKismetMathLibrary::FClamp(NewMana, 0.0f, m_fManaMax);
	m_fManaNormalized = UKismetMathLibrary::NormalizeToRange(m_fManaCurrent, 0.0f, m_fManaMax);
}

void UStatusComponent::F_ChangeAttackStrikingPower(float fValue, EOperatorType eOperator)
{
	if (m_fBuffAppliedStrikingPower > 0)
	{
		m_fAttackStrikingPower = CalculateChangeValue(m_fBuffAppliedStrikingPower, fValue, eOperator);
	}
	else
	{
		m_fAttackStrikingPower = CalculateChangeValue(m_fStrikingPower, fValue, eOperator);
	}
}

void UStatusComponent::F_ChangeBuffAppliedStrikingPower(float fValue, EOperatorType eOperator)
{
	m_fBuffAppliedStrikingPower = CalculateChangeValue(m_fStrikingPower, fValue, eOperator);
}

void UStatusComponent::F_ChangeBuffAppliedDefensivePower(float fValue, EOperatorType eOperator)
{
	m_fBuffAppliedDefensivePower = CalculateChangeValue(m_fDefensivePower, fValue, eOperator);
}

void UStatusComponent::F_ClearRegenTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ManaRegenTimerHandle);
}

float UStatusComponent::F_GetHealthCurrent()
{
	return m_fHealthCurrent;
}

float UStatusComponent::F_GetHealthMax()
{
	return m_fHealthMax;
}

float UStatusComponent::F_GetHealthNormalized()
{
	return m_fHealthNormalized;
}

float UStatusComponent::F_GetManaCurrent()
{
	return m_fManaCurrent;
}

float UStatusComponent::F_GetManaMax()
{
	return m_fManaMax;
}

float UStatusComponent::F_GetManaNormalized()
{
	return m_fManaNormalized;
}

uint8 UStatusComponent::F_GetLevel()
{
	return m_nLevel;
}

float UStatusComponent::F_GetStrikingPower()
{
	return m_fStrikingPower;
}

float UStatusComponent::F_GetDefensivePower()
{
	return m_fDefensivePower;
}

float UStatusComponent::F_GetAttackStrikingPower()
{
	return m_fAttackStrikingPower;
}

float UStatusComponent::F_GetBuffAppliedStrikingPower()
{
	return m_fBuffAppliedStrikingPower;
}

float UStatusComponent::F_GetBuffAppliedDefensivePower()
{
	return m_fBuffAppliedDefensivePower;
}
