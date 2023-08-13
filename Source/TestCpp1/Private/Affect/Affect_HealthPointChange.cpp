// Fill out your copyright notice in the Description page of Project Settings.


#include "Affect/Affect_HealthPointChange.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Player/TestCpp1Character.h"
#include "Monster/Monster.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "ActorComponent/MonsterStatusComponent.h"

UAffect_HealthPointChange::UAffect_HealthPointChange()
{
}

bool UAffect_HealthPointChange::F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator)
{
	if (Character)
	{
		ATestCpp1Character* Player = Cast<ATestCpp1Character>(Character);
		m_Interface_StatusComponent = Cast<IInterface_StatusComponent>(Player->F_GetPlayerStatusComponent());
		
		float HealthCurrent = Player->F_GetPlayerStatusComponent()->F_GetHealthCurrent();
		float HealthMax = Player->F_GetPlayerStatusComponent()->F_GetHealthMax();
		if (eOperator == EOperatorType::E_Plus)
		{
			if (HealthCurrent < HealthMax)
			{
				m_Interface_StatusComponent->F_AddHealth(fValue);
				return true;
			}
			else
			{
				m_AlertText = FText::FromString(FString::Printf(TEXT("HP가 가득 차 있습니다")));
				Player->F_GetGameMgr()->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&m_AlertText);
				return false;
			}
		}
	}
	return false;
}