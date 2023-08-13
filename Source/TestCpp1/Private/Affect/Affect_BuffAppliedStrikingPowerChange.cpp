// Fill out your copyright notice in the Description page of Project Settings.


#include "Affect/Affect_BuffAppliedStrikingPowerChange.h"
#include "Player/TestCpp1Character.h"
#include "Monster/Monster.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "ActorComponent/MonsterStatusComponent.h"

UAffect_BuffAppliedStrikingPowerChange::UAffect_BuffAppliedStrikingPowerChange()
{
}

bool UAffect_BuffAppliedStrikingPowerChange::F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator)
{
	if (Character)
	{
		if (Character->IsA(ATestCpp1Character::StaticClass()))
		{
			ATestCpp1Character* Player = Cast<ATestCpp1Character>(Character);
			m_Interface_StatusComponent = Cast<IInterface_StatusComponent>(Player->F_GetPlayerStatusComponent());
		}
		else if (Character->IsA(AMonster::StaticClass()))
		{
			AMonster* Monster = Cast<AMonster>(Character);
			m_Interface_StatusComponent = Cast<IInterface_StatusComponent>(Monster->F_GetMonsterStatusComponent());
		}
		m_Interface_StatusComponent->F_ChangeBuffAppliedStrikingPower(fValue, eOperator);
		return true;
	}
	return false;
}

void UAffect_BuffAppliedStrikingPowerChange::F_ResetApply(ACharacter* Character)
{
	if (Character)
	{
		if (Character->IsA(ATestCpp1Character::StaticClass()))
		{
			ATestCpp1Character* Player = Cast<ATestCpp1Character>(Character);
			m_Interface_StatusComponent = Cast<IInterface_StatusComponent>(Player->F_GetPlayerStatusComponent());
		}
		else if (Character->IsA(AMonster::StaticClass()))
		{
			AMonster* Monster = Cast<AMonster>(Character);
			m_Interface_StatusComponent = Cast<IInterface_StatusComponent>(Monster->F_GetMonsterStatusComponent());
		}
		m_Interface_StatusComponent->F_ResetBuffAppliedStrikingPower();
	}
}
