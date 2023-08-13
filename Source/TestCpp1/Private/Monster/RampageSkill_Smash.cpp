// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/RampageSkill_Smash.h"
#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "Skill/SkillDecal.h"
#include <Engine/Classes/Components/SphereComponent.h>
#include "Kismet/KismetSystemLibrary.h"
#include "Player/TestCpp1Character.h"
#include "BehaviorTree/BlackboardComponent.h"

ARampageSkill_Smash::ARampageSkill_Smash()
{
}

void ARampageSkill_Smash::BeginPlay()
{
	Super::BeginPlay();

	m_SpawnedSkillDecal = SpawnDecal();
	float PreSphereRadius = m_SpawnedSkillDecal->F_GetSkillRage()->GetScaledSphereRadius();
	m_SkillSphereRadius = 2.0f * PreSphereRadius;
	m_SpawnedSkillDecal->F_GetSkillRage()->SetSphereRadius(m_SkillSphereRadius);

	GetWorld()->GetTimerManager().SetTimer(m_ParticleTimerHandle, this, &ARampageSkill_Smash::CastComplete, 2.0f, false);
}

void ARampageSkill_Smash::CastComplete()
{
	AMonsterAIController* AIController = Cast<AMonsterAIController>(m_Monster->GetController());
	bool bDeath = AIController->GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::Key_bDeath);
	m_SpawnedSkillDecal->Destroy();
	if (!bDeath)
	{
		UAnimInstance* AnimInstance = m_Monster->GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(m_AnimMontage, 1.0f, EMontagePlayReturnType::MontageLength);
		AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimMontage);
	}
}

ASkillDecal* ARampageSkill_Smash::SpawnDecal()
{
	m_SpawnLocation = m_Monster->GetMesh()->GetBoneLocation(FName("ik_foot_root"));
	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, m_SpawnLocation, FVector(2.0f, 2.0f, 1.0f));
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return Cast<ASkillDecal>(World->SpawnActor<AActor>(m_SkillDecal, SpawnTransform, SpawnParameters));
}

void ARampageSkill_Smash::F_ApplySkillDamge(AActor* Player)
{
	Super::F_ApplySkillDamge(Player);
}

void ARampageSkill_Smash::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Super::PlayMontageNotifyBegin(NotifyName, BranchingPointNotifyPayload);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> arObjectTypes{};
	TEnumAsByte<EObjectTypeQuery> Player = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	arObjectTypes.Add(Player);
	TArray<AActor*> arIgnoredActors{};
	FHitResult OutHit{};
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), m_SpawnLocation, m_SpawnLocation, m_SkillSphereRadius, arObjectTypes, false, arIgnoredActors, EDrawDebugTrace::None, OutHit, true, FLinearColor::Red, FLinearColor::Green, 1.0f);
	AActor* HitActor = OutHit.GetActor();
	if (HitActor != nullptr && HitActor->IsA(ATestCpp1Character::StaticClass()))
	{
		F_ApplySkillDamge(HitActor);
	}
}

void ARampageSkill_Smash::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	Super::FunctionToExecuteOnAnimationEnd(animMontage, bInterrupted);
	DELE_SkillMontageEnd.Broadcast();
	Destroy();
}


