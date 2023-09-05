// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Affect/AffectType.h"
#include "AffectManager.generated.h"

class UAffect_Base;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API UAffectManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAffectManager();

protected:
	UPROPERTY()
	TArray<UAffect_base*> m_arAffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffectType m_eAffectType;

public:
	void F_Init();
	FORCEINLINE UAffect_base* F_GetAffect(EAffectType eAffect) const { return m_arAffect[(uint8)eAffect]; }
};
