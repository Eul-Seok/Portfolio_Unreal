
#include "ActorComponent/PlayerSkillsComponent.h"
#include "Skill/Skill_Base.h"

UPlayerSkillsComponent::UPlayerSkillsComponent():
	m_arPlayerSkillList{}, m_MapSkillUnlocks{}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerSkillsComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UPlayerSkillsComponent::F_AddSkill(FName SkillName)
{
	uint8* pCurrentSkillLevel = m_MapSkillUnlocks.Find(SkillName);
	if (pCurrentSkillLevel)
	{
		m_MapSkillUnlocks.Add(SkillName, (* pCurrentSkillLevel)+1);
		return true;
	}
	else
	{
		m_MapSkillUnlocks.Add(SkillName, 1);
		return true;
	}
}

bool UPlayerSkillsComponent::F_QuerySkill(FName SkillName, uint8& nSkillLevel)
{
	uint8* pCurrentSkillLevel = m_MapSkillUnlocks.Find(SkillName);
	if (pCurrentSkillLevel)
	{
		nSkillLevel = *pCurrentSkillLevel;
		return true;
	}
	else
	{
		nSkillLevel = 0;
		return false;
	}
}
