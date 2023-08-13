// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterAIController.generated.h"

UCLASS()
class TESTCPP1_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIController(const FObjectInitializer& ObjectInitializer);

	static const FName Key_Player;
	static const FName Key_MosterState;
	static const FName Key_PatrolLocation;
	static const FName Key_Distance;
	static const FName Key_bDeath;

public:
	void BeginPlay() override;
	void OnPossess(APawn* pawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerception;
	class UAISenseConfig_Sight* SightConfig;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class UBehaviorTree* BTAsset;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class UBlackboardData* BBAsset;
	class ATestCpp1Character* m_Player;
	FDelegateHandle m_DelegateHandle;

protected:
	UFUNCTION()
	void SetPerceptionSystem();
	UFUNCTION()
	void SetPlayer(AActor* Player);
	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);
	UFUNCTION()
	void CallResetPlayer();

public:
	FTimerHandle m_PerceptionTimer;

};
