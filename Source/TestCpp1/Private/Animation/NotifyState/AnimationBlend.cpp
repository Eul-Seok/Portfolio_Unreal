// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/AnimationBlend.h"
#include "Animation/Anim_Base.h"

void UAnimationBlend::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp && MeshComp->GetOwner())
	{
		UAnim_Base* AnimInstance = Cast<UAnim_Base>(MeshComp->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->F_SetIsBlend(true);
		}
	}
}

void UAnimationBlend::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp && MeshComp->GetOwner())
	{
		UAnim_Base* AnimInstance = Cast<UAnim_Base>(MeshComp->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->F_SetIsBlend(false);
		}
	}
}
