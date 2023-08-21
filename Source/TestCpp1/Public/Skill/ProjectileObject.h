// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Skill/SkillData.h"
#include "ProjectileObject.generated.h"

class IInterface_StatusComponent;

UCLASS()
class TESTCPP1_API AProjectileObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileObject();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* RootSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovement;
	
protected:
	IInterface_StatusComponent* m_Interface_CasterStatusComponent;
	IInterface_StatusComponent* m_Interface_TargetStatusComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_HitImpact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_HitGroundImpact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* m_HitSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bStunSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fStunDuration;
	FName m_SkillRowName;
	FSkillData* m_PlayerSkillData;
	FVector m_vHitImpactVector;
	ACharacter* m_pCaster;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	void InitProjectile();
	float ApplySkillAffect(AActor* Caster, AActor* Target);

public:
	void F_ActivateProjectile(USceneComponent* TargetComponent, bool bHoming);

public:
	void F_SetCaster(ACharacter* pCaster);

protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
