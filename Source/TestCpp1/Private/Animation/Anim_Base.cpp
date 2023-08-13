// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Anim_Base.h"
#include "Player/TestCpp1Character.h"
#include "Player/MyPlayerController.h"
#include "Monster/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnim_Base::UAnim_Base():
	bJumpInput{}, bFalling{}, bJump{}, bTargeting{}, bTurn{}, Speed{}, Direction{}, TimeDelta{}, rRotatorInterp{}, PitchDelta{}, YawDelta{}, YawDeltaThreshold{}, m_IsBlend{}, m_Player{}, m_Monster{}, m_PlayerController{}
{

}

void UAnim_Base::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Initialize();
}

void UAnim_Base::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Initialize();
}

void UAnim_Base::Initialize()
{
	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		if (Pawn->IsA(ATestCpp1Character::StaticClass()))
		{
			m_Player = Cast<ATestCpp1Character>(Pawn);
			if (m_Player->GetController())
			{
				m_PlayerController = Cast<AMyPlayerController>(m_Player->GetController());
				m_PlayerController->DELE_ToggleTargetingMode.BindUFunction(this, FName("F_CallToggleTargetingMode"));
			}
		}
		else
		{
			m_Monster = Cast<AMonster>(Pawn);
		}
	}

	YawDeltaThreshold = 30.0f;
}

void UAnim_Base::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	APawn* Pawn = TryGetPawnOwner();
	if (m_Player == nullptr && m_Monster == nullptr)
	{
		return;
	}
	if (m_Player && m_PlayerController)
	{
		bJumpInput = m_PlayerController->F_GetIsJumpInput();
		bFalling = m_Player->GetMovementComponent()->IsFalling();
		bJump = bJumpInput && bFalling;
		m_PlayerController->F_SetIsJumpInput(bFalling);
	}	
	TimeDelta = DeltaSeconds;
	Speed = Pawn->GetVelocity().Size2D();
	Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());

	rRotatorInterp = UKismetMathLibrary::RInterpTo(FRotator(0.0f, PitchDelta, YawDelta), UKismetMathLibrary::NormalizedDeltaRotator(Pawn->GetBaseAimRotation(), Pawn->GetActorRotation()), TimeDelta, 0.0f);
	PitchDelta = UKismetMathLibrary::ClampAngle(rRotatorInterp.Pitch, -90.0f, 90.0f);
	YawDelta = rRotatorInterp.Yaw;
	bTurn = UKismetMathLibrary::Abs(YawDelta) > YawDeltaThreshold;
}

void UAnim_Base::F_CallToggleTargetingMode()
{
	bTargeting = m_PlayerController->F_GetIsTargetingMode();
}

void UAnim_Base::F_SetIsBlend(bool bBlend)
{
	m_IsBlend = bBlend;
}

float UAnim_Base::F_GetDirection()
{
	return Direction;
}
