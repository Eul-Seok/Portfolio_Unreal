// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_Melee.h"
#include "Skill_Projectile.generated.h"

UCLASS()
class TESTCPP1_API ASkill_Projectile : public ASkill_Melee
{
	GENERATED_BODY()
	
public:
	ASkill_Projectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AProjectileObject> m_ProjectileClass;
	AProjectileObject* m_ProjectileObject;

protected:
	void SpawnProjectileObject();

public:
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) override;
};
