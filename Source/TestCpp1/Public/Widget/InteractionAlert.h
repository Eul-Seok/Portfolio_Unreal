// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionAlert.generated.h"

UENUM(BlueprintType)
enum class EInteractionAlertType : uint8
{
	E_Default = 0				UMETA(DisplayName = Default),
	E_Interact					UMETA(DisplayName = Interact),
	E_InteractPickup 			UMETA(DisplayName = InteractPickup),
	E_InteractionAlertType_Max	UMETA(DisplayName = InteractionAlertType_Max)
};


UCLASS()
class TESTCPP1_API UInteractionAlert : public UUserWidget
{
	GENERATED_BODY()

public:
	UInteractionAlert(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Interact;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Interact_PickUp;
		

public:
	void F_Display(EInteractionAlertType InteractionAlertType);

};

