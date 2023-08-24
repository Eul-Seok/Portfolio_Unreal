// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon_Base.h"
#include "Particles/ParticleSystemComponent.h"
#include "Monster/Monster.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/PlayerStatusComponent.h"

AWeapon_Base::AWeapon_Base():
	TrailParticleSystemComponent{}, m_setHitObject{}, m_fWeaponDamage{}, m_bKnockBackAttack{}, m_bStunAttack{}
{
	TrailParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	TrailParticleSystemComponent->AttachToComponent(ItemMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ItemMesh->SetGenerateOverlapEvents(false);
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Base::OnOverlapBegin);
}

void AWeapon_Base::F_SetAttackAvailable(bool IsAvailable)
{
	ItemMesh->SetGenerateOverlapEvents(IsAvailable);
	bool bGenerateOverlabEvents = ItemMesh->GetGenerateOverlapEvents();
	if (bGenerateOverlabEvents)
	{
		m_setHitObject.Empty();
	}
}

void AWeapon_Base::F_BeginTrail(float TrailWidth)
{
	TrailParticleSystemComponent->BeginTrails(FName("1"), FName("2"), ETrailWidthMode::ETrailWidthMode_FromCentre, TrailWidth);
}

void AWeapon_Base::F_EndTrail()
{
	TrailParticleSystemComponent->EndTrails();
}

void AWeapon_Base::F_SetbKnockBackAttack(bool IsKnockBack)
{
	m_bKnockBackAttack = IsKnockBack;
}

void AWeapon_Base::F_SetbStunAttack(bool IsStun)
{
	m_bStunAttack = IsStun;
}

void AWeapon_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString TargetName = OtherActor->GetName();
	if (OtherActor->ActorHasTag(FName("Monster")) && !(GetAttachParentActor()->IsA(AMonster::StaticClass())))
	{
		AMonster* Monster = Cast<AMonster>(OtherActor);
		if (!m_setHitObject.Contains(TargetName))
		{
			m_setHitObject.Add(TargetName);
			Monster->F_Hit(OverlappedComp);
		}
	}
	else if (OtherActor->ActorHasTag(FName("Player"))&& !(GetAttachParentActor()->IsA(ATestCpp1Character::StaticClass())))
	{
		ATestCpp1Character* Player = Cast<ATestCpp1Character>(OtherActor);
		if (!m_setHitObject.Contains(TargetName))
		{
			m_setHitObject.Add(TargetName);
			Player->F_Hit(OverlappedComp);
			if (m_bKnockBackAttack && Player->F_GetPlayerStatusComponent()->F_GetHealthCurrent() > 0)
			{
				Player->F_PlayKnockBack();
			}
			else if (m_bStunAttack && Player->F_GetPlayerStatusComponent()->F_GetHealthCurrent() > 0)
			{
				Player->F_PlayStun();
			}
		}
	}

}

