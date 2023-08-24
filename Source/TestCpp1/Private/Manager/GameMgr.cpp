// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GameMgr.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/InventoryManager.h"
#include "Manager/ItemManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/AffectManager.h"
#include "Manager/SkillManager.h"
#include "Player/TestCpp1Character.h"
#include "NPC/NPC.h"
#include "Quest/QuestLog.h"
#include "Skill/Skill_Base.h"
#include "ActorComponent/PlayerSkillsComponent.h"

#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Widget/SkillWindow.h"
#include "Widget/SkillSlot.h"


AGameMgr::AGameMgr():
	m_pInventoryMgr{}, m_pItemMgr{}, m_pWidgetMgr{}, m_pAffectMgr{}, m_pSkillMgr{}, m_pSoundMgr{}, m_QuestLogComponent{}, m_Player{}
{
	m_pInventoryMgr = CreateDefaultSubobject<UInventoryManager>(TEXT("m_pInventoryMgr"));
	m_pItemMgr = CreateDefaultSubobject<UItemManager>(TEXT("m_pItemMgr"));
	m_pWidgetMgr = CreateDefaultSubobject<UWidgetManager>(TEXT("m_pWidgetMgr"));
	m_pAffectMgr = CreateDefaultSubobject<UAffectManager>(TEXT("m_pAffectMgr"));
	m_pSkillMgr = CreateDefaultSubobject<USkillManager>(TEXT("m_pSkillMgr"));
	m_pSoundMgr = CreateDefaultSubobject<USoundManager>(TEXT("m_pSoundMgr"));
	m_QuestLogComponent = CreateDefaultSubobject<UQuestLog>(TEXT("m_QuestLogComponent"));
}

void AGameMgr::BeginPlay()
{
	Super::BeginPlay();
	Init_Managers();
	m_pWidgetMgr->F_ShowGameMethod();
	DELE_GameClear.AddUFunction(this, FName("GameClear"));
	TestSetting();
}

void AGameMgr::Init_Managers()
{
	m_pAffectMgr->F_Init();
	m_pInventoryMgr->F_Init(7, 6);
	m_pSkillMgr->F_Init(1, 6);
	m_pItemMgr->F_Init();
	m_pWidgetMgr->F_Init();
	
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	TArray<TSubclassOf<ASkill_Base>>* arPlayerSkill = m_Player->F_GetPlayerSkillsComponent()->F_GetPlayerSkillList();
	uint8 nPlayerSkillsLength = (*arPlayerSkill).Num();
	for (uint8 nSkillIndex = 0; nSkillIndex < nPlayerSkillsLength; nSkillIndex++)
	{
		m_pSkillMgr->F_PlayerSkillsRegistration(nSkillIndex);
	}
}

void AGameMgr::GameClear()
{
	m_pWidgetMgr->F_ToggleGameClearMenu();
}

void AGameMgr::TestSetting()
{
	uint8 nNum = 2;
	FName ItemRowName = FName("HealthPotion");
	for (uint8 i = 0; i < nNum; i++)
	{
		m_pInventoryMgr->F_ItemAdd(&ItemRowName);
		(*m_pWidgetMgr->F_GetSkillWindow()->F_GetarSkillSlot())[i]->F_SkillLevelUp();
		(*m_pWidgetMgr->F_GetQuickSlotWindow()->F_GetQuickSlotArray())[i]->F_QuickSlotRegistration(ESlotType::E_InventorySlot, i);
		(*m_pWidgetMgr->F_GetQuickSlotWindow()->F_GetQuickSlotArray())[i + nNum]->F_QuickSlotRegistration(ESlotType::E_SkillSlot, i);
	}
}

void AGameMgr::F_NPCUpdateTextRenderHasQuest()
{
	TArray<AActor*> arWorldNPC;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPC::StaticClass(), arWorldNPC);
	for (int i = 0; i < arWorldNPC.Num(); ++i)
	{
		Cast<ANPC>(arWorldNPC[i])->DELE_UpdateTextRenderHasQuest.Broadcast();
	}
}

