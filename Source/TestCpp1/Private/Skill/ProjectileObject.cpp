// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/ProjectileObject.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include <Engine/Classes/Components/SphereComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TestCpp1Character.h"
#include "Skill/SkillDecal.h"
#include "Skill/Skill_Base.h"
#include "Monster/MonsterSkill_Base.h"
#include "Monster/Monster.h"
#include "ActorComponent/MonsterStatusComponent.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "Manager/GameMgr.h"
#include "Manager/SkillManager.h"

AProjectileObject::AProjectileObject():
	RootSphere{}, StaticMesh{}, ProjectileMovement{}, m_Interface_CasterStatusComponent{}, m_Interface_TargetStatusComponent{}, ParticleSystemComponent{},
	m_HitImpact{}, m_HitGroundImpact{}, m_HitSound{}, m_bStunSkill{}, m_fStunDuration{}, m_SkillRowName{}, m_PlayerSkillData{}, m_vHitImpactVector{}, m_pCaster{}
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootSphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	RootComponent = RootSphere;
	StaticMesh->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetupAttachment(StaticMesh);

	InitProjectile();
	InitialLifeSpan = 5.0f;
}

void AProjectileObject::InitProjectile()
{
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bAutoActivate = true;
}

float AProjectileObject::ApplySkillAffect(AActor* Caster, AActor* Target)
{
	float fCasterSkillStrikingPower{};
	float fCasterStrikingPower{};
	if (Caster->IsA(ATestCpp1Character::StaticClass()))
	{
		m_Interface_CasterStatusComponent = Cast<IInterface_StatusComponent>(Cast<ATestCpp1Character>(Caster)->F_GetPlayerStatusComponent());
		m_Interface_TargetStatusComponent = Cast<IInterface_StatusComponent>(Cast<AMonster>(Target)->F_GetMonsterStatusComponent());
	}
	else if (Caster->IsA(AMonster::StaticClass()))
	{
		m_Interface_CasterStatusComponent = Cast<IInterface_StatusComponent>(Cast<AMonster>(Caster)->F_GetMonsterStatusComponent());
		m_Interface_TargetStatusComponent = Cast<IInterface_StatusComponent>(Cast<ATestCpp1Character>(Target)->F_GetPlayerStatusComponent());
	}
	fCasterStrikingPower = m_Interface_CasterStatusComponent->F_GetStrikingPower();
	fCasterSkillStrikingPower = fCasterStrikingPower;

	float fTargetDefensivePower = m_Interface_TargetStatusComponent->F_GetDefensivePower();
	if (m_PlayerSkillData)
	{
		float fSkillAffectValue = m_PlayerSkillData->m_AffectValue;
		if (fSkillAffectValue > 0.0f)
		{
			fCasterStrikingPower = m_Interface_CasterStatusComponent->F_GetStrikingPower();
			
			uint8 nSkillLevel = Cast<ATestCpp1Character>(m_pCaster)->F_GetGameMgr()->F_GetSkillMgr()->F_GetSpawnSkillLevel();
			float fSkillIncrementValue = 0.1f;
			fCasterSkillStrikingPower = fCasterStrikingPower * (fSkillAffectValue + (fSkillIncrementValue * (float)(nSkillLevel - 1)));
		}
	}
	float fFinalDamage = fCasterSkillStrikingPower - fTargetDefensivePower;
	if (fFinalDamage < 1)
	{
		fFinalDamage = 1;
	}
	return fFinalDamage;
}

void AProjectileObject::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectileObject::OnOverlapBegin);
	ASkill_Base* PlayerSkill = Cast<ASkill_Base>(GetOwner());
	if (PlayerSkill)
	{
		m_SkillRowName = *PlayerSkill->F_GetSkillRowName();
		UDataTable* pSkillDataTable = PlayerSkill->F_GetSkillDataTable();
		m_PlayerSkillData = pSkillDataTable->FindRow<FSkillData>(m_SkillRowName, "");
	}
}

void AProjectileObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileObject::F_ActivateProjectile(USceneComponent* TargetComponent, bool bHoming)
{
	StaticMesh->SetGenerateOverlapEvents(true);
	ProjectileMovement->Activate();
	if (bHoming)
	{
		ProjectileMovement->bIsHomingProjectile = true;
		ProjectileMovement->HomingAccelerationMagnitude = 100000.0f;
		ProjectileMovement->HomingTargetComponent = TargetComponent;
	}
}

void AProjectileObject::F_SetCaster(ACharacter* pCaster)
{
	m_pCaster = pCaster;
}

void AProjectileObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector vImpactPoint{};
	OverlappedComp->GetClosestPointOnCollision(OtherActor->GetActorLocation(), vImpactPoint);

	if (OtherActor->IsA(ATestCpp1Character::StaticClass()))
	{
		ATestCpp1Character* Player = Cast<ATestCpp1Character>(OtherActor);
		Player->F_ApplyHitDamage(ApplySkillAffect(m_pCaster, OtherActor), &vImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_HitImpact, vImpactPoint);
		if (m_bStunSkill && Player->F_GetPlayerStatusComponent()->F_GetHealthCurrent() > 0.0f)
		{
			Player->F_PlayStun(m_fStunDuration);
		}
	}
	else if (OtherActor->IsA(AMonster::StaticClass()))
	{
		Cast<AMonster>(OtherActor)->F_ApplyHitDamage(ApplySkillAffect(m_pCaster, OtherActor), &vImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_HitImpact, vImpactPoint);
	}
	else if (OtherActor->IsA(ASkillDecal::StaticClass()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_HitGroundImpact, vImpactPoint);
		OtherActor->Destroy();
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_HitSound, vImpactPoint);
}
