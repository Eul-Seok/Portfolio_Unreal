// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillDecal.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include <Engine/Classes/Components/SphereComponent.h>
#include <Engine/Classes/Components/SceneComponent.h>

ASkillDecal::ASkillDecal():
	RootScene{}, OverlapSphere{}, DecalStaticMesh{}, SkillRage{}
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	DecalStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SkillRage = CreateDefaultSubobject<USphereComponent>(TEXT("SkillRange"));
	RootComponent = RootScene;
	OverlapSphere->SetupAttachment(RootComponent);
	DecalStaticMesh->SetupAttachment(RootComponent);
	SkillRage->SetupAttachment(DecalStaticMesh);
}

USceneComponent* ASkillDecal::F_GetRootScene()
{
	return RootScene;
}

USphereComponent* ASkillDecal::F_GetOverlapSphere()
{
	return OverlapSphere;
}

USphereComponent* ASkillDecal::F_GetSkillRage()
{
	return SkillRage;
}
