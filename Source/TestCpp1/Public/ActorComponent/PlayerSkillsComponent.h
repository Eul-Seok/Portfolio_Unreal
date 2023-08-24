// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSkillsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTCPP1_API UPlayerSkillsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerSkillsComponent();

protected:
	virtual void BeginPlay() override;

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class ASkill_Base>> m_arPlayerSkillList;
	UPROPERTY()
	TMap<FName, uint8> m_MapSkillUnlocks;

public:
	bool F_AddSkill(FName SkillName);
	bool F_QuerySkill(FName SkillName, uint8& nSkillLevel);
	FORCEINLINE TArray<TSubclassOf<ASkill_Base>>* F_GetPlayerSkillList() { return &m_arPlayerSkillList; }
};
