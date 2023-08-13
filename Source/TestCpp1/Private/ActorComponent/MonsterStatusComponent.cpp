

#include "ActorComponent/MonsterStatusComponent.h"
#include "Monster/Monster.h"

UMonsterStatusComponent::UMonsterStatusComponent()
{	
	Init();
}

void UMonsterStatusComponent::Init()
{
	m_fHealthMax = 100.0f;
	m_fHealthCurrent = m_fHealthMax;

	m_fManaMax = 100.0f;
	m_fManaCurrent = m_fManaMax;
}

void UMonsterStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<AMonster>(GetOwner())->DELE_TargetDeath.AddUFunction(this, FName("CallClearRegenTimer"));
	GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &UMonsterStatusComponent::HealthRegenTick, 30.0f, true);
}

void UMonsterStatusComponent::HealthRegenTick()
{
	Super::HealthRegenTick();
	if (m_fHealthCurrent < m_fHealthMax)
	{
		float NewHealth = m_fHealthCurrent + (m_fHealthMax * 0.05f);
		m_fHealthCurrent = UKismetMathLibrary::FClamp(NewHealth, 0.0f, m_fHealthMax);
		m_fHealthNormalized = UKismetMathLibrary::NormalizeToRange(m_fHealthCurrent, 0.0f, m_fHealthMax);
		Cast<AMonster>(GetOwner())->DELE_TargetStatusBarUpdate.ExecuteIfBound();
		Cast<AMonster>(GetOwner())->DELE_TargetStatusBarMiniUpdate.ExecuteIfBound();
	}
}

void UMonsterStatusComponent::CallClearRegenTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimerHandle);
}

void UMonsterStatusComponent::F_ReduceHealth(float fValue)
{
	Super::F_ReduceHealth(fValue);
	Cast<AMonster>(GetOwner())->DELE_TargetStatusBarUpdate.ExecuteIfBound();
	Cast<AMonster>(GetOwner())->DELE_TargetStatusBarMiniUpdate.ExecuteIfBound();
}
