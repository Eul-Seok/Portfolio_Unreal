// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_Base.generated.h"

UCLASS()
class TESTCPP1_API UAnim_Base : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnim_Base();

public:
	virtual void NativeBeginPlay();
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bJumpInput;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bFalling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bTargeting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TimeDelta;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator rRotatorInterp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PitchDelta;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float YawDelta;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float YawDeltaThreshold;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool m_IsBlend;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ATestCpp1Character* m_Player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMonster* m_Monster;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMyPlayerController* m_PlayerController;

private:
	void Initialize();

public:
	UFUNCTION()
	void F_CallToggleTargetingMode();
	UFUNCTION()
	void F_SetIsBlend(bool bBlend);
	float F_GetDirection();
};
