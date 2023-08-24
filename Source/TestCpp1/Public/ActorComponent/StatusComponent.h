// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Interface_StatusComponent.h"
#include "Affect/OperatorType.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StatusComponent.generated.h"

DECLARE_DELEGATE(FDele_Single);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTCPP1_API UStatusComponent : public UActorComponent, public IInterface_StatusComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 m_nLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fHealthMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fHealthCurrent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float m_fHealthNormalized;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fManaMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fManaCurrent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float m_fManaNormalized;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fStrikingPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_fDefensivePower;
	
	float m_fAttackStrikingPower;
	float m_fBuffAppliedStrikingPower;
	float m_fBuffAppliedDefensivePower;

protected:
	virtual void BeginPlay() override;
	virtual void HealthRegenTick() override;
	virtual void ManaRegenTick() override;
	virtual float CalculateChangeValue(float fStatus, float fValue, EOperatorType eOperator) override;

public:	
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
	virtual void F_ClearRegenTimer() override;
	

public:
	FORCEINLINE float F_GetHealthCurrent() { return m_fHealthCurrent; }
	FORCEINLINE float F_GetHealthMax() { return m_fHealthMax; }
	FORCEINLINE float F_GetHealthNormalized() { return m_fHealthNormalized; }
	FORCEINLINE float F_GetManaCurrent() { return m_fManaCurrent; }
	FORCEINLINE float F_GetManaMax() { return m_fManaMax; }
	FORCEINLINE float F_GetManaNormalized() { return m_fManaNormalized; }
	FORCEINLINE uint8 F_GetLevel() { return m_nLevel; }



public:
	FORCEINLINE virtual float F_GetStrikingPower() override { return m_fStrikingPower; }
	FORCEINLINE virtual float F_GetDefensivePower() override { return m_fDefensivePower; }
	FORCEINLINE float F_GetAttackStrikingPower() { return m_fAttackStrikingPower; }
	FORCEINLINE float F_GetBuffAppliedStrikingPower() { return m_fBuffAppliedStrikingPower; }
	FORCEINLINE float F_GetBuffAppliedDefensivePower() { return m_fBuffAppliedDefensivePower; }

public:
	FDele_Single DELE_RequestUpdateStatusBar;
	FTimerHandle HealthRegenTimerHandle;	
	FTimerHandle ManaRegenTimerHandle;
};
