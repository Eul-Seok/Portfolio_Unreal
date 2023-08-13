// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillData.h"

FSkillData::FSkillData():
	m_SkillWeaponType{}, m_SkillClass{}, m_SkillName{}, m_SkillDescription{}, m_SkillImage{}, m_AffectType{}, m_AffectOperator{}, m_AffectValue{}, m_Cost{}, m_CoolDownTime{}, m_CastTime{},
	m_SkillPoint{}, m_MaxSkillLevel{}, m_PreRequisiteSkillName{}, m_PreRequisiteSkillLevel{}, m_IsInterruptable{}, m_RequiresTarget{}, m_Enable{}
{
}
