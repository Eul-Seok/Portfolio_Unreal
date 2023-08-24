// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillDecal.generated.h"

UCLASS()
class TESTCPP1_API ASkillDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillDecal();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* OverlapSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DecalStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SkillRage;

public:	
	FORCEINLINE USceneComponent* F_GetRootScene() { return RootScene; }
	FORCEINLINE USphereComponent* F_GetOverlapSphere() { return OverlapSphere; }
	FORCEINLINE USphereComponent* F_GetSkillRage() { return SkillRage; }
};
