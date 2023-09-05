// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SkillManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/GameMgr.h"
#include "Skill/Skill_Base.h"
#include "Widget/SkillWindow.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Widget/SkillSlot.h"
#include "Widget/HeadsUpDisplay.h"
#include "Kismet/GameplayStatics.h"
#include "ActorComponent/PlayerSkillsComponent.h"
#include "Player/MyPlayerController.h"
#include "Player/TestCpp1Character.h"

USkillManager::USkillManager():
	m_pGameMgr{}, m_Player{}, m_nSkillRowCount{}, m_nSkillColumnCount{}, m_nLength{}, m_pSkillDataTable{}, m_QuickSlotMap{}, m_nSpawnSkillLevel{}, m_pSkillDataDefault{}
{
}

bool USkillManager::SpawnSkill(uint8 Index, const FSkillData* SkillData, ACharacter* pTarget)
{
	ASkill_Base* pSpawnSkill{};
	UWorld* world = GetWorld();
	FTransform SpawnTransform = m_Player->GetTransform();
	TSubclassOf<ASkill_Base> Skill = SkillData->m_SkillClass;
	pSpawnSkill = GetWorld()->SpawnActorDeferred<ASkill_Base>(Skill, SpawnTransform, m_Player, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (pSpawnSkill != nullptr)
	{
		(*F_GetSkillSlotArray())[Index]->F_CheckSkillLevel(m_nSpawnSkillLevel);
		pSpawnSkill->F_SetCaster(m_Player);
		if (pTarget != nullptr)
		{
			pSpawnSkill->F_SetTarget(pTarget);
		}
		(*F_GetSkillSlotArray())[Index]->F_BindCooldownTimer(pSpawnSkill);
		pSpawnSkill->FinishSpawning(SpawnTransform);
		return true;
	}
	return false;
}

void USkillManager::F_Init(uint8 nSkillWindowRow, uint8 nSkillWindowColumn)
{
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	m_nSkillRowCount = nSkillWindowRow;
	m_nSkillColumnCount = nSkillWindowColumn;
	m_nLength = nSkillWindowRow * nSkillWindowColumn;
	m_nSkillWeaponTypeCount = ((uint8)ESkillWeaponType::E_SkillWeaponType_Max) - 1;
	m_pSkillDataDefault = m_pSkillDataTable->FindRow<FSkillData>(FName("Default"), "");
	m_QuickSlotMap.Reserve(m_nLength * m_nSkillWeaponTypeCount);
	for (uint8 Index = 0; Index < m_nLength * m_nSkillWeaponTypeCount; Index++)
	{
		m_QuickSlotMap.Emplace(Index, EQuickSlotNumber::E_Default);
	}

	m_nKatanaSkillSlotIndex = 0;
	m_nCommonSkillSlotIndex = m_nLength;
}

bool USkillManager::F_UseSkill(uint8 Index)
{
	bool bSuccess{};
	EQuickSlotNumber eQuickSlotNumber{};
	uint8 nPairQuickSlotIndex{};
	UQuickSlot* PairQuickSlot{};

	if ((*F_GetSkillSlotArray()).IsValidIndex(Index) && (*F_GetSkillSlotArray())[Index]->F_GetbPurchased())
	{	
		eQuickSlotNumber = F_GetQuickSlotMapValue(Index);
		nPairQuickSlotIndex = (uint8)eQuickSlotNumber - 1;
		PairQuickSlot = (*m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_GetQuickSlotArray())[nPairQuickSlotIndex];
		FSkillData* SkillData = (*F_GetSkillSlotArray())[Index]->F_GetSkillData();
		if (SkillData->m_SkillWeaponType == m_Player->F_GetCurrentSkillWeaponType() || SkillData->m_SkillWeaponType == ESkillWeaponType::E_Common)
		{
			if (!SkillData->m_RequiresTarget)
			{
				bSuccess = SpawnSkill(Index, SkillData);
			}
			else
			{
				ACharacter* pTarget = Cast<ACharacter>(Cast<AMyPlayerController>(m_Player->GetController())->F_GetCurrentTarget());
				if (pTarget)
				{
					bSuccess = SpawnSkill(Index, SkillData, pTarget);
				}
				else
				{
					FText AlertText = FText::FromString(FString::Printf(TEXT("타겟을 지정해주세요")));
					m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
					m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
					return bSuccess;
				}
			}
		}
		else
		{
			FText AlertText = FText::FromString(FString::Printf(TEXT("알맞는 무기를 착용해주세요")));
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
			m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
			return bSuccess;
		}
	}
	return bSuccess;
}

void USkillManager::F_PlayerSkillsRegistration(uint8 Index)
{
	TArray<TSubclassOf<ASkill_Base>>* arPlayerSkill = m_Player->F_GetPlayerSkillsComponent()->F_GetPlayerSkillList();
	if ((*arPlayerSkill).IsValidIndex(Index))
	{
		TSubclassOf<ASkill_Base> Skill = (*arPlayerSkill)[Index];
		FSkillData* PlayerSkillData = m_pSkillDataTable->FindRow<FSkillData>(*Skill.GetDefaultObject()->F_GetSkillRowName(), "");
		if (PlayerSkillData->m_SkillWeaponType == ESkillWeaponType::E_Katana)
		{
			(*F_GetSkillSlotArray())[m_nKatanaSkillSlotIndex]->F_SetSkillData(PlayerSkillData);
			(*F_GetSkillSlotArray())[m_nKatanaSkillSlotIndex]->F_SetSkillSlotIcon();
			m_nKatanaSkillSlotIndex++;
		}
		else if (PlayerSkillData->m_SkillWeaponType == ESkillWeaponType::E_Common)
		{
			(*F_GetSkillSlotArray())[m_nCommonSkillSlotIndex]->F_SetSkillData(PlayerSkillData);
			(*F_GetSkillSlotArray())[m_nCommonSkillSlotIndex]->F_SetSkillSlotIcon();
			m_nCommonSkillSlotIndex++;
		}
	}
}

void USkillManager::F_SetQuickSlotMap(uint8 SkillWindowIndex, EQuickSlotNumber eQuickSlotNumber)
{
	m_QuickSlotMap.Emplace(SkillWindowIndex, eQuickSlotNumber);
}

TArray<USkillSlot*>* USkillManager::F_GetSkillSlotArray() const
{
	return m_pGameMgr->F_GetWidgetMgr()->F_GetSkillWindow()->F_GetarSkillSlot();
}
