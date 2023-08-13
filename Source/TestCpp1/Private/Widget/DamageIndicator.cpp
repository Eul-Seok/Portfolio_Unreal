// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageIndicator.h"
#include "Components/TextBlock.h"

UDamageIndicator::UDamageIndicator(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UDamageIndicator::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayAnimationForward(Fade);
}

void UDamageIndicator::F_SetDamage(float fDamage)
{
	m_fDamage = fDamage;
	Text_Damage->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), m_fDamage)));
}
