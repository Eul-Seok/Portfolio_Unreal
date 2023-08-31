// Fill out your copyright notice in the Description page of Project Settings.


#include "Affect/Affect_base.h"

UAffect_base::UAffect_base() :
	m_Interface_StatusComponent{}
{
}

bool UAffect_base::F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator)
{
	return false;
}

void UAffect_base::F_ResetApply(ACharacter* Character)
{

}
