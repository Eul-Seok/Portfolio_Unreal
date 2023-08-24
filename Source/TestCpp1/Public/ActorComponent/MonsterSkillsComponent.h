// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterSkillsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTCPP1_API UMonsterSkillsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMonsterSkillsComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AMonsterSkill_Base>> m_MonsterSKillList;
	
public:
	FORCEINLINE TArray<TSubclassOf<AMonsterSkill_Base>>* F_GetMonsterSkillList() { return &m_MonsterSKillList; }
};
