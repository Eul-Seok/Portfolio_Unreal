// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/RampageSkill_StoneThrow.h"
#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "Skill/SkillDecal.h"
#include "Skill/ProjectileObject.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/TestCpp1Character.h"

ARampageSkill_StoneThrow::ARampageSkill_StoneThrow()
{
	m_fCastTime = 1.0f;
}

void ARampageSkill_StoneThrow::BeginPlay()
{
	Super::BeginPlay();
	UAnimInstance* AnimInstance = m_Monster->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(m_AnimMontage, 1.0f, EMontagePlayReturnType::MontageLength);
	AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimMontage);
	m_SpawnedSkillDecal = SpawnDecal();
	GetWorld()->GetTimerManager().SetTimer(m_ParticleTimerHandle, this, &ARampageSkill_StoneThrow::Throw, m_fCastTime, false);
}

void ARampageSkill_StoneThrow::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (!m_bHasStone)
	{
		CreateStone();
	}
	else
	{
		m_ProjectileObject->F_ActivateProjectile(m_SpawnedSkillDecal->F_GetRootScene(), true);
		m_ProjectileObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Super::PlayMontageNotifyBegin(NotifyName, BranchingPointNotifyPayload);
	}
}

void ARampageSkill_StoneThrow::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	Super::FunctionToExecuteOnAnimationEnd(animMontage, bInterrupted);
	DELE_SkillMontageEnd.Broadcast();
	if (bInterrupted)
	{
		m_SpawnedSkillDecal->Destroy();
		m_ProjectileObject->Destroy();
	}
	Destroy();
}

void ARampageSkill_StoneThrow::CreateStone()
{
	UWorld* World = GetWorld();
	FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);
	m_ProjectileObject = World->SpawnActorDeferred<AProjectileObject>(m_ProjectileClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (m_ProjectileObject)
	{		
		m_ProjectileObject->F_SetCaster(Cast<ACharacter>(GetOwner()));
		m_ProjectileObject->FinishSpawning(SpawnTransform);
	}
	m_ProjectileObject->AttachToComponent(m_Monster->F_GetSceneStoneObject(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_bHasStone = true;
}

void ARampageSkill_StoneThrow::Throw()
{
	UAnimInstance* AnimInstance = m_Monster->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_JumpToSection(FName("Throw"));

}

void ARampageSkill_StoneThrow::CalculatePlayerGroundLocation(const FVector& TargetLocation, FVector& TargetGroundLocation)
{
	float TraceDistance = 500.0f;
	FHitResult HitResult{};
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TargetLocation, TargetLocation - FVector(0, 0, TraceDistance), ECC_WorldStatic))
	{
		TargetGroundLocation = HitResult.Location;
	}
	else
	{
		TargetGroundLocation = TargetLocation;
	}
}

ASkillDecal* ARampageSkill_StoneThrow::SpawnDecal()
{
	FVector PlayerGroundLocation{};
	FVector PlayerLocation = Cast<ATestCpp1Character>(Cast<AMonsterAIController>(m_Monster->GetController())->GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::Key_Player))->GetMesh()->GetBoneLocation(FName("ik_foot_root"));
	CalculatePlayerGroundLocation(PlayerLocation, PlayerGroundLocation);
	UWorld* World = GetWorld();
	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, PlayerGroundLocation, FVector(1.0f, 1.0f, 1.0f));
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return Cast<ASkillDecal>(World->SpawnActor<AActor>(m_SkillDecal, SpawnTransform, SpawnParameters));;
}
