// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widget/QuickSlotNumber.h"
#include "Skill/SkillData.h"
#include "SkillManager.generated.h"

class USkillSlot;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API USkillManager : public UActorComponent
{
	GENERATED_BODY()

public:
	USkillManager();

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class ATestCpp1Character* m_Player;
	UPROPERTY()
	uint8 m_nSkillRowCount;
	UPROPERTY()
	uint8 m_nSkillColumnCount;
	UPROPERTY()
	uint8 m_nLength;
	UPROPERTY()
	uint8 m_nSkillWeaponTypeCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* m_pSkillDataTable;
	UPROPERTY()
	TMap<uint8, EQuickSlotNumber> m_QuickSlotMap;
	UPROPERTY()
	uint8 m_nSpawnSkillLevel;
	
	FSkillData* m_pSkillDataDefault;
	uint8 m_nKatanaSkillSlotIndex;
	uint8 m_nCommonSkillSlotIndex;
	
protected:
	bool SpawnSkill(uint8 Index, const FSkillData* SkillData, ACharacter* pTarget = nullptr);

public:
	void F_Init(uint8 nSkillWindowRow, uint8 nSkillWindowColumn);
	bool F_UseSkill(uint8 Index);
	void F_PlayerSkillsRegistration(uint8 Index);
public:
	void F_SetQuickSlotMap(uint8 SkillWindowIndex, EQuickSlotNumber eQuickSlotNumber);

	FSkillData* F_GetSkillDataDefault();
	uint8 F_GetLength();
	uint8 F_GetRowCount();
	uint8 F_GetColumnCount();
	uint8 F_GetQuickSlotMapKey(EQuickSlotNumber eQuickSlotNumber);
	EQuickSlotNumber F_GetQuickSlotMapValue(uint8 SkillWindowIndex);
	TArray<USkillSlot*>* F_GetSkillSlotArray();
	uint8 F_GetSpawnSkillLevel();
};
