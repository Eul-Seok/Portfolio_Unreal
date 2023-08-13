// Fill out your copyright notice in the Description page of Project Settings.


#include "Affect/Affect_ManaPointChange.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Player/TestCpp1Character.h"
#include "Monster/Monster.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "ActorComponent/MonsterStatusComponent.h"

UAffect_ManaPointChange::UAffect_ManaPointChange()
{
}

bool UAffect_ManaPointChange::F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator)
{
	if (Character)
	{
		if (eOperator == EOperatorType::E_Plus)
		{
			ATestCpp1Character* Player = Cast<ATestCpp1Character>(Character);
			m_Interface_StatusComponent = Cast<IInterface_StatusComponent>(Player->F_GetPlayerStatusComponent());

			float ManaCurrent = Player->F_GetPlayerStatusComponent()->F_GetManaCurrent();
			float ManaMax = Player->F_GetPlayerStatusComponent()->F_GetManaMax();
			if (ManaCurrent < ManaMax)
			{
				m_Interface_StatusComponent->F_AddMana(fValue);
				return true;
			}
			else
			{
				m_AlertText = FText::FromString(FString::Printf(TEXT("MP가 가득 차 있습니다")));
				Player->F_GetGameMgr()->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&m_AlertText);
				return false;
			}
		}
	}
	return false;
}
