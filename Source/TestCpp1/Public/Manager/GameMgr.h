// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Manager/SoundManager.h"
#include "GameMgr.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS()
class TESTCPP1_API AGameMgr : public AGameStateBase
{
	GENERATED_BODY()

public:
	AGameMgr();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryManager* m_pInventoryMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemManager* m_pItemMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetManager* m_pWidgetMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAffectManager* m_pAffectMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkillManager* m_pSkillMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundManager* m_pSoundMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UQuestLog* m_QuestLogComponent;

	class ATestCpp1Character* m_Player;
	

protected:
	virtual void BeginPlay() override;
	
protected:
	void Init_Managers();
	UFUNCTION()
	void GameClear();
	void TestSetting();

public:
	void F_NPCUpdateTextRenderHasQuest();
	UInventoryManager* F_GetInventoryMgr();
	UItemManager* F_GetItemMgr();
	UWidgetManager* F_GetWidgetMgr();
	UAffectManager* F_GetAffectMgr();
	USkillManager* F_GetSkillMgr();
	USoundManager* F_GetSoundMgr();
	
	UQuestLog* F_GetQuestLogComponent();

public:
	FDele_Multi DELE_GameClear;
};
