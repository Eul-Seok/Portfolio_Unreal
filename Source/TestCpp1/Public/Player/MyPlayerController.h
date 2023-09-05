// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


DECLARE_DELEGATE(FDele_Single);
DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS()
class TESTCPP1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY()
	class ATestCpp1Character* m_Player;
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class AMonster* m_pCurrentTarget;
	bool m_bJumpInput;
	bool m_bTargetingMode;
	uint8 m_nTargetingIndex;

protected:
	void BindPlayerAction();
	void BindUseQuickSlotAction();
	void BindUseWidgetAction();
	void BindAxis();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();
	void StopJumping();
	void ItemGet();
	void Interact();
	void DefaultAttack();
	void WeaponEquip();

	void ToggleInventory();
	void ToggleSkillWindow();
	void ToggleStatusWindow();
	void ToggleQuestWindow();
	void TogglePauseMenu();
	void CloseUI();
	void UseQuickSlot1();
	void UseQuickSlot2();
	void UseQuickSlot3();
	void UseQuickSlot4();
	void UseQuickSlot5();
	void UseQuickSlot6();
	void UseQuickSlot7();
	void UseQuickSlot8();
	void UseQuickSlot9();
	void UseQuickSlot10();
	void UseQuickSlot11();
	void UseQuickSlot12();
	void UseQuickSlot13();
	void UseQuickSlot14();
	void Evasion();
	void TargetingShift();
	
public:
	void F_ToggleTargetingMode();
	void F_TargetClear();
	void F_InputModePlayerStun(bool bStun);
	void F_InputModePlayerDeath();
	void F_InputModePlayerRevival();
	void F_InputIgnoreToggle(bool bIgnore);

public:
	UFUNCTION()
	void F_SetIsJumpInput(bool IsFalling);
	void F_SetCurrentTarget(AMonster* Monster);

public:
	FORCEINLINE AMonster* F_GetCurrentTarget() const { return m_pCurrentTarget; }
	FORCEINLINE bool F_GetIsJumpInput() const { return m_bJumpInput; }
	FORCEINLINE bool F_GetIsTargetingMode() const { return m_bTargetingMode; }

public:
	FDele_Single DELE_ToggleTargetingMode;
	FDele_Single DELE_InterruptCasting;
	FDele_Multi DELE_TargetChange;
	FDele_Multi DELE_TargetCancled;
};

