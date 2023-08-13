// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestCpp1GameMode.generated.h"

UCLASS(minimalapi)
class ATestCpp1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestCpp1GameMode();
protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<class UMainMenu> W_StartingMainMenuWidgetClass;
};



