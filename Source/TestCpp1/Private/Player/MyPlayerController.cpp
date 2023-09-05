// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Player/TestCpp1Character.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Item/Item.h"
#include "Widget/QuickSlotWindow.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Monster/Monster.h"
#include "NPC/NPC.h"
#include "Animation/Anim_Base.h"

AMyPlayerController::AMyPlayerController() :
	m_Player{}, m_pGameMgr{}, m_bJumpInput{}, m_bTargetingMode{}
{
	bEnableClickEvents = true;
	bEnableTouchEvents = false;

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	m_Player = Cast<ATestCpp1Character>(GetCharacter());
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	BindPlayerAction();
	BindUseQuickSlotAction();
	BindUseWidgetAction();
	BindAxis();
}


void AMyPlayerController::BindPlayerAction()
{
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJumping);
	InputComponent->BindAction("PickUp", IE_Released, this, &AMyPlayerController::ItemGet);
	InputComponent->BindAction("Interact", IE_Released, this, &AMyPlayerController::Interact);
	InputComponent->BindAction("DefaultAttack", IE_Pressed, this, &AMyPlayerController::DefaultAttack);
	InputComponent->BindAction("WeaponEquip", IE_Released, this, &AMyPlayerController::WeaponEquip);
	InputComponent->BindAction("ToggleTargetingMode", IE_Released, this, &AMyPlayerController::F_ToggleTargetingMode);
	InputComponent->BindAction("TargetingShift", IE_Released, this, &AMyPlayerController::TargetingShift);
	InputComponent->BindAction("Evasion", IE_Released, this, &AMyPlayerController::Evasion);
}

void AMyPlayerController::BindUseQuickSlotAction()
{
	InputComponent->BindAction("Quick1", IE_Released, this, &AMyPlayerController::UseQuickSlot1);
	InputComponent->BindAction("Quick2", IE_Released, this, &AMyPlayerController::UseQuickSlot2);
	InputComponent->BindAction("Quick3", IE_Released, this, &AMyPlayerController::UseQuickSlot3);
	InputComponent->BindAction("Quick4", IE_Released, this, &AMyPlayerController::UseQuickSlot4);
	InputComponent->BindAction("Quick5", IE_Released, this, &AMyPlayerController::UseQuickSlot5);
	InputComponent->BindAction("Quick6", IE_Released, this, &AMyPlayerController::UseQuickSlot6);
	InputComponent->BindAction("Quick7", IE_Released, this, &AMyPlayerController::UseQuickSlot7);
	InputComponent->BindAction("Quick8", IE_Released, this, &AMyPlayerController::UseQuickSlot8);
	InputComponent->BindAction("Quick9", IE_Released, this, &AMyPlayerController::UseQuickSlot9);
	InputComponent->BindAction("Quick10", IE_Released, this, &AMyPlayerController::UseQuickSlot10);
	InputComponent->BindAction("Quick11", IE_Released, this, &AMyPlayerController::UseQuickSlot11);
	InputComponent->BindAction("Quick12", IE_Released, this, &AMyPlayerController::UseQuickSlot12);
	InputComponent->BindAction("Quick13", IE_Released, this, &AMyPlayerController::UseQuickSlot13);
	InputComponent->BindAction("Quick14", IE_Released, this, &AMyPlayerController::UseQuickSlot14);
}

void AMyPlayerController::BindUseWidgetAction()
{
	InputComponent->BindAction("Inventory", IE_Released, this, &AMyPlayerController::ToggleInventory);
	InputComponent->BindAction("SkillWindow", IE_Released, this, &AMyPlayerController::ToggleSkillWindow);
	InputComponent->BindAction("StatusWindow", IE_Released, this, &AMyPlayerController::ToggleStatusWindow);
	InputComponent->BindAction("QuestWindow", IE_Released, this, &AMyPlayerController::ToggleQuestWindow);
	InputComponent->BindAction("PauseMenu", IE_Released, this, &AMyPlayerController::TogglePauseMenu);
	InputComponent->BindAction("CloseUI", IE_Released, this, &AMyPlayerController::CloseUI);
}

void AMyPlayerController::BindAxis()
{
	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AMyPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyPlayerController::AddPitchInput);
}

void AMyPlayerController::MoveForward(float Value)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn && (Value != 0.0f))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		MyPawn->AddMovementInput(Direction, Value);
		if (m_Player->F_GetbCasting())
		{
			DELE_InterruptCasting.ExecuteIfBound();
		}
	}

}

void AMyPlayerController::MoveRight(float Value)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn && (Value != 0.0f))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		MyPawn->AddMovementInput(Direction, Value);
		if (m_Player->F_GetbCasting())
		{
			DELE_InterruptCasting.ExecuteIfBound();
		}
	}
}

void AMyPlayerController::Jump()
{
	m_Player->bPressedJump = true;
	m_bJumpInput = true;
}

void AMyPlayerController::StopJumping()
{
	m_Player->bPressedJump = false;
}

void AMyPlayerController::ItemGet()
{
	TSet<AItem*>* setOverLapItem = m_Player->F_GetOverLapItem();
	if ((*setOverLapItem).Num() > 0)
	{
		(*setOverLapItem).Array()[0]->F_ItemGet(m_Player);
	}
}

void AMyPlayerController::Interact()
{
	ANPC* NPC = m_Player->F_GetOverlapNPC();
	if (NPC)
	{
		NPC->F_RotateToFacePlayer(m_Player);
		NPC->F_InteractionNPC();
		if (NPC->F_CheckHasQuest())
		{
			NPC->F_DisplayQuestContent();
		}
	}
}

void AMyPlayerController::DefaultAttack()
{
	m_Player->F_DefaultAttack(); 
}

void AMyPlayerController::WeaponEquip()
{
	m_Player->F_OneHandWeaponEquipped();
}

void AMyPlayerController::ToggleInventory()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_Inventory);
}

void AMyPlayerController::ToggleSkillWindow()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_SkillWindow);
}

void AMyPlayerController::ToggleStatusWindow()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_StatusWindow);
}

void AMyPlayerController::ToggleQuestWindow()
{
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestWindow);
}

void AMyPlayerController::TogglePauseMenu()
{
	UWidgetManager* WidgetManager = m_pGameMgr->F_GetWidgetMgr();
	if (!WidgetManager->F_GetbOpenedAnyUI())
	{
		WidgetManager->F_TogglePauseMenu();
	}
}

void AMyPlayerController::CloseUI()
{
	UWidgetManager* WidgetManager = m_pGameMgr->F_GetWidgetMgr();
	if (WidgetManager->F_GetbOpenedAnyUI())
	{
		WidgetManager->F_CloseAllUI();
	}
}

void AMyPlayerController::UseQuickSlot1()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(0);
}

void AMyPlayerController::UseQuickSlot2()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(1);
}

void AMyPlayerController::UseQuickSlot3()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(2);
}

void AMyPlayerController::UseQuickSlot4()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(3);
}

void AMyPlayerController::UseQuickSlot5()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(4);
}

void AMyPlayerController::UseQuickSlot6()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(5);
}

void AMyPlayerController::UseQuickSlot7()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(6);
}

void AMyPlayerController::UseQuickSlot8()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(7);
}

void AMyPlayerController::UseQuickSlot9()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(8);
}

void AMyPlayerController::UseQuickSlot10()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(9);
}

void AMyPlayerController::UseQuickSlot11()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(10);
}

void AMyPlayerController::UseQuickSlot12()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(11);
}

void AMyPlayerController::UseQuickSlot13()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(12);
}

void AMyPlayerController::UseQuickSlot14()
{
	m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotUse(13);
}

void AMyPlayerController::Evasion()
{
	UAnimInstance* AnimInstance = m_Player->GetMesh()->GetAnimInstance();
	float Direction = Cast<UAnim_Base>(AnimInstance)->F_GetDirection();
	m_Player->F_Evasion(Direction);
}

void AMyPlayerController::TargetingShift()
{
	if (m_bTargetingMode)
	{
		TSet<AMonster*>* setOverlapMonster = m_Player->F_GetOverLapMonster();
		uint8 nOverlapMonsterCount = (*setOverlapMonster).Num();
		if (nOverlapMonsterCount > m_nTargetingIndex + 1)
		{
			m_nTargetingIndex++;
		}
		else if (nOverlapMonsterCount <= m_nTargetingIndex + 1)
		{
			m_nTargetingIndex = 0;
		}
		m_pCurrentTarget->F_CallClearTargetIndicator();
		m_pCurrentTarget = (*setOverlapMonster).Array()[m_nTargetingIndex];
		m_pCurrentTarget->F_UpdateTarget();
		DELE_TargetChange.Broadcast();
	}
	else
	{
		F_ToggleTargetingMode();
	}
}

void AMyPlayerController::F_ToggleTargetingMode()
{
	if (!m_bTargetingMode)
	{
		m_nTargetingIndex = 0;
		TSet<AMonster*>* setOverlapMonster = m_Player->F_GetOverLapMonster();
		uint8 nOverlapMonsterCount = (*setOverlapMonster).Num();
		if (nOverlapMonsterCount > m_nTargetingIndex)
		{
			m_Player->F_TargetingModeOn();
			m_bTargetingMode = true;
			m_pCurrentTarget = (*setOverlapMonster).Array()[m_nTargetingIndex];
			m_pCurrentTarget->F_UpdateTarget();
			DELE_TargetChange.Broadcast();
			DELE_ToggleTargetingMode.ExecuteIfBound();
		}
		else
		{
			FText AlertText = FText::FromString(FString::Printf(TEXT("일정 범위 내에 대상이 없습니다")));
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
		}
	}
	else
	{
		DELE_TargetCancled.Broadcast();
	}
}

void AMyPlayerController::F_TargetClear()
{
	m_Player->F_TargetingModeOff();
	m_bTargetingMode = false;
	m_pCurrentTarget = nullptr;
	DELE_ToggleTargetingMode.ExecuteIfBound();
}

void AMyPlayerController::F_InputModePlayerStun(bool bStun)
{
	if (bStun)
	{
		F_InputModePlayerDeath();
		BindUseQuickSlotAction();
		BindUseWidgetAction();
	}
	else
	{
		F_InputIgnoreToggle(false);
		BindPlayerAction();
	}
}

void AMyPlayerController::F_InputModePlayerDeath()
{
	F_InputIgnoreToggle(true);
	InputComponent->ClearActionBindings();
}

void AMyPlayerController::F_InputModePlayerRevival()
{
	F_InputIgnoreToggle(false);
	BindPlayerAction();
	BindUseQuickSlotAction();
	BindUseWidgetAction();
}

void AMyPlayerController::F_InputIgnoreToggle(bool bIgnore)
{
	if (bIgnore)
	{
		SetIgnoreMoveInput(true);
		SetIgnoreLookInput(true);
	}
	else
	{
		SetIgnoreMoveInput(false);
		SetIgnoreLookInput(false);		
	}
}

void AMyPlayerController::F_SetIsJumpInput(bool IsFalling)
{
	m_bJumpInput = IsFalling;
}

void AMyPlayerController::F_SetCurrentTarget(AMonster* Monster)
{
	m_pCurrentTarget = Monster;
}
