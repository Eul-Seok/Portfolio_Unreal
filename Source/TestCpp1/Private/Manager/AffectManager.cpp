// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/AffectManager.h"
#include "Affect/Affect_base.h"
#include "Affect/Affect_Default.h"
#include "Affect/Affect_HealthPointChange.h"
#include "Affect/Affect_ManaPointChange.h"
#include "Affect/Affect_AttackStrikingPowerChange.h"
#include "Affect/Affect_BuffAppliedStrikingPowerChange.h"
#include "Affect/Affect_BuffAppliedDefensivePowerChange.h"

UAffectManager::UAffectManager():
	m_arAffect{}, m_eAffectType{}
{
}

void UAffectManager::F_Init()
{
	m_arAffect.Reserve((uint8)EAffectType::E_Affect_Max);
	m_arAffect.EmplaceAt((uint8)EAffectType::E_Default, NewObject<UAffect_Default>(this, TEXT("Default")));
	m_arAffect.EmplaceAt((uint8)EAffectType::E_HealthPointChange, NewObject<UAffect_HealthPointChange>(this, TEXT("HealthPointChagne")));
	m_arAffect.EmplaceAt((uint8)EAffectType::E_ManaPointChange, NewObject<UAffect_ManaPointChange>(this, TEXT("ManaPointChagne")));
	m_arAffect.EmplaceAt((uint8)EAffectType::E_AttackStrikingPowerChange, NewObject<UAffect_AttackStrikingPowerChange>(this, TEXT("AttackStrikingPowerChange")));
	m_arAffect.EmplaceAt((uint8)EAffectType::E_BuffAppliedStrikingPowerChange, NewObject<UAffect_BuffAppliedStrikingPowerChange>(this, TEXT("BuffAppliedStrikingPowerChange")));
	m_arAffect.EmplaceAt((uint8)EAffectType::E_BuffAppliedDefensivePowerChange, NewObject<UAffect_BuffAppliedDefensivePowerChange>(this, TEXT("BuffAppliedDefensivePowerChange")));
}

UAffect_base* UAffectManager::F_GetAffect(EAffectType eAffect)
{
	return m_arAffect[(uint8)eAffect];
}
