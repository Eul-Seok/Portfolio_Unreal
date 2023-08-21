// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationMarker.generated.h"

UENUM(BlueprintType)
enum class ELocationMarkerType : uint8
{
	E_Default = 0					UMETA(DisplayName = Default),
	E_QuestLocation					UMETA(DisplayName = QuestLocation),
	E_LevelSequenceLoaction		UMETA(DisplayName = LevelSequenceLoaction),
	E_QuestTypeMax					UMETA(DisplayName = LocationMarkerTypeMax)
};

class AItem;

UCLASS()
class TESTCPP1_API ALocationMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	ALocationMarker();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* LocationReachedCollision;

protected:
	class AGameMgr* m_pGameMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELocationMarkerType m_eLocationMarkerType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> m_CheckItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMonsterSpawner* m_pMonsterSpawner;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class ALevelSequenceActor* m_LevelSequenceActor;

protected:
	void PlayLevelSequence();
	UFUNCTION()
	void MonsterSpawn();

public:	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
