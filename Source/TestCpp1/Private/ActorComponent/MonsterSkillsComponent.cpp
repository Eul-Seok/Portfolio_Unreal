
#include "ActorComponent/MonsterSkillsComponent.h"
#include "Monster/MonsterSkill_Base.h"

UMonsterSkillsComponent::UMonsterSkillsComponent():
	m_MonsterSKillList{}
{
	PrimaryComponentTick.bCanEverTick = false;
}
