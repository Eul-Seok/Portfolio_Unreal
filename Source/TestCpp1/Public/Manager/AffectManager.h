// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Affect/AffectType.h"
#include "AffectManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API UAffectManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAffectManager();

protected:
	UPROPERTY()
	TArray<class UAffect_base*> m_arAffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffectType m_eAffectType;

public:
	void F_Init();
	UAffect_base* F_GetAffect(EAffectType);
};
