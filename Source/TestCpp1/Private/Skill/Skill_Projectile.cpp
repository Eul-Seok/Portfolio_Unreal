// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_Projectile.h"
#include "Skill/ProjectileObject.h"
#include "Player/TestCpp1Character.h"
#include "Player/MyPlayerController.h"

ASkill_Projectile::ASkill_Projectile():
	m_ProjectileClass{}, m_ProjectileObject{}
{
}

void ASkill_Projectile::SpawnProjectileObject()
{
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = m_pCaster->GetActorTransform();
	m_ProjectileObject = World->SpawnActorDeferred<AProjectileObject>(m_ProjectileClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (m_ProjectileObject)
	{
		m_ProjectileObject->F_SetCaster(m_pCaster);
		m_ProjectileObject->FinishSpawning(SpawnTransform);
	}
}

void ASkill_Projectile::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Super::PlayMontageNotifyBegin(NotifyName, BranchingPointNotifyPayload);
	SpawnProjectileObject();
}
