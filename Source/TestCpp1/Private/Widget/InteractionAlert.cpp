// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InteractionAlert.h"
#include "Components/CanvasPanel.h"

UInteractionAlert::UInteractionAlert(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UInteractionAlert::F_Display(EInteractionAlertType InteractionAlertType)
{
	if (InteractionAlertType == EInteractionAlertType::E_Interact)
	{
		Interact->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Interact_PickUp->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Interact_PickUp->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Interact->SetVisibility(ESlateVisibility::Hidden);
	}
}