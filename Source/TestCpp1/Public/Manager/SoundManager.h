// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundManager.generated.h"

UENUM(BlueprintType)
enum class EPlaySound : uint8
{
	E_Default = 0				UMETA(DisplayName = Default),
	E_SoundOpenUI				UMETA(DisplayName = OpenUI),
	E_SoundItemPickUp			UMETA(DisplayName = ItemPickUp),
	E_SoundItemDrop			UMETA(DisplayName = ItemDrop),
	E_SoundItemDestroy			UMETA(DisplayName = ItemDestroy),
	E_SoundDrink				UMETA(DisplayName = Drink),
	E_SoundDoNotUse				UMETA(DisplayName = DoNotUse),
	E_SoundLevelUp				UMETA(DisplayName = LevelUp),
	E_SoundQuestAccept			UMETA(DisplayName = QuestAccept),
	E_SoundQuestSingleObjectiveComplete UMETA(DisplayName = QuestSingleObjectiveComplete),
	E_SoundQuestComplete		UMETA(DisplayName = QuestComplete),
	E_PlaySound_Max				UMETA(DisplayName = PlaySound_Max)
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API USoundManager : public UActorComponent
{
	GENERATED_BODY()
	
public:
	USoundManager();

protected:
	UPROPERTY()
	TArray<USoundBase*> m_arSound;

public:
	void F_PlaySound(EPlaySound Sound);
};
