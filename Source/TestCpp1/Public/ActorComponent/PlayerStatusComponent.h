// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/StatusComponent.h"
#include "Player/PlayerLevelUpData.h"
#include "PlayerStatusComponent.generated.h"

DECLARE_DELEGATE(FDele_Single);
DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UENUM(BlueprintType)
enum class EPlayerStatus : uint8
{
	E_Default = 0		UMETA(DisplayName = Default),
	E_Strength			UMETA(DisplayName = Strength),
	E_Agility			UMETA(DisplayName = Agility),
	E_Constitution		UMETA(DisplayName = Constitution),
	E_Intelligence		UMETA(DisplayName = Intelligence),
	E_PlayerStatus_Max	UMETA(DisplayName = PlayerStatus_Max)
};

UCLASS()
class TESTCPP1_API UPlayerStatusComponent : public UStatusComponent
{
	GENERATED_BODY()

public:
	UPlayerStatusComponent();

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	ATestCpp1Character* m_Player;
	float m_fExpMax;
	float m_fExpCurrent;
	float m_fExpNormalized;
	UPROPERTY()
	UDataTable* m_pPlayerLevelUpDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_ParticleLevelUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 m_nStrength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 m_nAgility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 m_nConstitution;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 m_nIntelligence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fIncrementPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fIncrementStatusBar;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 m_nIncrementStatusPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 m_nIncrementSkillPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 m_nStatusPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 m_nSkillPoint;

protected:
	virtual void BeginPlay() override;
	virtual void HealthRegenTick() override;
	virtual void ManaRegenTick() override;
	void Init();
	void LevelUp();
	void LevelUpReward();
	void UpdateApplyBuff(const ATestCpp1Character* Player);

public:
	void F_CompleteRecovery();
	virtual void F_AddHealth(float fValue) override;
	virtual void F_AddMana(float fValue) override;
	virtual void F_ReduceHealth(float fValue) override;
	virtual void F_ReduceMana(float fValue) override;
	virtual void F_ChangeAttackStrikingPower(float fValue, EOperatorType eOperator) override;
	virtual void F_ChangeBuffAppliedStrikingPower(float fValue, EOperatorType eOperator) override;
	virtual void F_ChangeBuffAppliedDefensivePower(float fValue, EOperatorType eOperator) override;
	virtual void F_ResetAttackStrikingPower() override;
	virtual void F_ResetBuffAppliedStrikingPower() override;
	virtual void F_ResetBuffAppliedDefensivePower() override;
	void F_AddExp(float fValue);
	void F_StatusUpApply(EPlayerStatus eStatus);
	void F_SetRegenTimer();

public:
	void F_SetSkillPoint(uint8 nNewSkillPoint);
	void F_SetStrikingPower(float fNewStrikingPower);
	void F_SetDefensivePower(float fNewDefensivePower);
	void F_SetStrength(uint8 nNewStrength);
	void F_SetAgility(uint8 nNewAgility);
	void F_SetConstitution(uint8 nNewConstitution);
	void F_SetIntelligence(uint8 nNewIntelligence);
	void F_SetStatusPoint(uint8 nNewStatusPoint);

public:
	FORCEINLINE float F_GetExpMax() { return m_fExpMax; }
	FORCEINLINE float F_GetExpCurrent() { return m_fExpCurrent; }
	FORCEINLINE float F_GetExpNormalized() { return m_fExpNormalized; }
	FORCEINLINE uint8 F_GetStrength() { return m_nStrength; }
	FORCEINLINE uint8 F_GetAgility() { return m_nAgility; }
	FORCEINLINE uint8 F_GetConstitution(){ return m_nConstitution; }
	FORCEINLINE uint8 F_GetIntelligence() { return m_nIntelligence; }
	FORCEINLINE uint8 F_GetSkillPoint() { return m_nSkillPoint; }
	FORCEINLINE uint8 F_GetStatusPoint() { return m_nStatusPoint; }

public:
	FDele_Multi DELE_RequestUpdateStatusBar;
	FDele_Single DELE_RequestUpdatePower;
	FDele_Multi DELE_LevelUp;
	
};





