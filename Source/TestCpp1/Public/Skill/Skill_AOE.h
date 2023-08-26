
#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_Melee.h"
#include "Skill_AOE.generated.h"

UCLASS()
class TESTCPP1_API ASkill_AOE : public ASkill_Melee
{
	GENERATED_BODY()

public:
	ASkill_AOE();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_SkillSphereRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_StartLocationFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_EndLocationFactor;
	FVector m_SpawnStartLocation;
	FVector m_SpawnEndLocation;
	UPROPERTY()
	TArray<FHitResult> m_arOutHit;
	FHitResult* m_pOutHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_HitImpact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_HitGroundImpact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* m_HitSound;

protected:
	virtual void BeginPlay() override;
	virtual void ApplySkillAffect() override;
	void SpawnImpact();

public:
	virtual void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) override;
};
