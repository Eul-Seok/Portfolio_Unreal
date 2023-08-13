// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Affect/AffectType.h"
#include "Affect/OperatorType.h"
#include "Skill/SkillWeaponType.h"
#include "SkillData.generated.h"

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FSkillData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillWeaponType m_SkillWeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASkill_Base> m_SkillClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_SkillDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* m_SkillImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffectType m_AffectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOperatorType m_AffectOperator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_AffectValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CoolDownTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CastTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 m_SkillPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 m_MaxSkillLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_PreRequisiteSkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 m_PreRequisiteSkillLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsInterruptable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_RequiresTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_Enable;
};
