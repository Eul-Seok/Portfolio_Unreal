// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class AMonster;

UCLASS()
class TESTCPP1_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonsterSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SpawnSphere;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float m_fSpawnRadius;	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	uint8 m_nMaxMonsterCount;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<AMonster> m_MonsterClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float m_fSpawnTimeInterval;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool m_bSpawnLoop;

	uint8 m_nMonsterCount;
	FTimerHandle m_SpawnTimerHandle;

protected:
	virtual void BeginPlay() override;
	void SpawnerAction();

public:
	void F_RemoveMonster();
	void F_MonsterSpawn();

};
