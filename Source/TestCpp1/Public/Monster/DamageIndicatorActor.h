// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DamageIndicatorActor.generated.h"

UCLASS()
class TESTCPP1_API ADamageIndicatorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageIndicatorActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Scene_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* Widget_DamageIndicator;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCurveFloat* CurveFloat_Move;
	FTimeline Timeline_Move;

protected:
	float m_fDamage;
	FVector m_vStartLocation;
	FVector m_vEndLocation;

protected:
	UFUNCTION()
	void Move();
	UFUNCTION()
	void ActorDestroy();

public:
	void F_SetDamage(float fDamage);

};
