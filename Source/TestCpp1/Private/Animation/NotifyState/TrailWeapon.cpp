// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/TrailWeapon.h"
#include "Player/TestCpp1Character.h"
#include "Item/Weapon_Base.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

void UTrailWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp && MeshComp->GetOwner())
	{
		ATestCpp1Character* Player = Cast<ATestCpp1Character>(MeshComp->GetOwner());
		if (Player && Player->F_GetRightHandWeapon())
		{
			Player->F_GetRightHandWeapon()->F_GetTrail()->SetTemplate(m_Trail);
			Player->F_GetRightHandWeapon()->F_BeginTrail(m_TrailWidth);
		}
	}
}

	void UTrailWeapon::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
	{
		Super::NotifyEnd(MeshComp, Animation);
		if (MeshComp && MeshComp->GetOwner())
		{
			ATestCpp1Character* Player = Cast<ATestCpp1Character>(MeshComp->GetOwner());
			if (Player && Player->F_GetRightHandWeapon())
			{
				Player->F_GetRightHandWeapon()->F_EndTrail();
			}
		}
	}
