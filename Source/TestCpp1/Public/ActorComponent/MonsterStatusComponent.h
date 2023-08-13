// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/StatusComponent.h"
#include "MonsterStatusComponent.generated.h"

UCLASS()
class TESTCPP1_API UMonsterStatusComponent : public UStatusComponent
{
	GENERATED_BODY()

public:
	UMonsterStatusComponent();

protected:
	virtual void BeginPlay() override;
	virtual void HealthRegenTick() override;
	void Init();
	UFUNCTION()
	void CallClearRegenTimer();
	

public:
	virtual void F_ReduceHealth(float fValue) override;	
};
