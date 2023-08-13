
#include "Monster/RampageSkill_Buff.h"
#include "Monster/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "ActorComponent/MonsterStatusComponent.h"
#include "Interface/Interface_Affect.h"
#include "Manager/GameMgr.h"
#include "Manager/AffectManager.h"
#include "Affect/Affect_base.h"

ARampageSkill_Buff::ARampageSkill_Buff():
	m_fBuffDuration{}
{
	m_fBuffDuration = 20.0f;
}

void ARampageSkill_Buff::BeginPlay()
{
	Super::BeginPlay();
	UAnimInstance* AnimInstance = m_Monster->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(m_AnimMontage, 1.0f, EMontagePlayReturnType::MontageLength);
	AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimMontage);
}

void ARampageSkill_Buff::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	Super::FunctionToExecuteOnAnimationEnd(animMontage, bInterrupted);
	m_SpawnedSkillParticle = UGameplayStatics::SpawnEmitterAttached(m_SkillParticle, Cast<AMonster>(GetOwner())->GetMesh(), NAME_None, FVector(ForceInit),FRotator::ZeroRotator, FVector((FVector)((8.0f))), EAttachLocation::SnapToTarget);
	GetWorld()->GetTimerManager().SetTimer(m_ParticleTimerHandle, this, &ARampageSkill_Buff::ResetEffect, m_fBuffDuration, false);
	DELE_SkillMontageEnd.Broadcast();
	ActivateEffect();
}

void ARampageSkill_Buff::ResetEffect()
{
	Super::ResetEffect();
	m_SpawnedSkillParticle->DestroyComponent();
	if (m_fAffectValue != 0)
	{
		m_Interface_Affect->F_ResetApply(m_Monster);
	}
	Destroy();
}

void ARampageSkill_Buff::ActivateEffect()
{
	Super::ActivateEffect();
	if (m_fAffectValue != 0)
	{
		m_Interface_Affect = Cast<IInterface_Affect>(m_Monster->F_GetGameMgr()->F_GetAffectMgr()->F_GetAffect(m_eAffectType));
		m_Interface_Affect->F_Apply(m_Monster, m_fAffectValue, EOperatorType::E_Multiply);

	}
}




