// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AttackType.h"
#include "Monster.generated.h"

DECLARE_DELEGATE(FDele_Single);
DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS()
class TESTCPP1_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_DamageIndicator;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_StoneObject;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_WeaponLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* ChildActor_WeaponLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_WeaponRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* ChildActor_WeaponRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_HitBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* HitBoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDecalComponent* TargetIndicator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* Widget_TargetBarMini;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMonsterStatusComponent* MonsterStatusComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMonsterSkillsComponent* MonsterSkillsComponent;

protected:
	FTimerHandle m_MonsterDeathTimer;
	FTimerHandle m_MonsterDestroyTimer;
	FTimerHandle m_MonsterTargetBarTimer;
	FTimerHandle m_MonsterRenderCustomDepthTimer;
	UPROPERTY(BlueprintReadOnly)
	class AGameMgr* m_pGameMgr;
	UPROPERTY(BlueprintReadOnly)
	class ATestCpp1Character* m_Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_AttackImpact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> m_arAnimDefaultAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimKnockBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimDeath;
	UPROPERTY()
	class AWeapon_Base* m_LeftWeapon;
	UPROPERTY()
	class AWeapon_Base* m_RightWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBossMonster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_MonsterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> m_DamageIndicator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AItem>> m_arRewardItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_RewardExp;
	class AMonsterSpawner* m_Spawner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_PatrolSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_ChaseSpeed;
	bool m_bAttacking;
	FVector m_TargetActorLocation;
	FDelegateHandle m_HandleTargetCancled;
	FDelegateHandle m_HandleUpdateTargetStatusBar;

	class UTargetBarMini* m_TargetBarMini;
	bool bDisplayTargetBarMini;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton)override;

protected:
	void RemoveBinding();
	void CheckQuestMonster();
	void MonsterDie(const FVector* pHitImactVector);
	void MonsterSink();
	void MonsterDestroy();
	void Ragdoll(const FVector* pHitImactVector);
	float CalculateHitDamage(const UPrimitiveComponent* pOverlappedComp);
	void Reward();
	void UpdateWidgetRotation();
	void DisplayTargetHealthBarMini();
	void CallHiddenTargetBarMini();
	void RenderCustomDepthOn();
	void RenderCustomDepthOff();
	void DisplayDamageIndicator(float fDamage);

public:
	void F_UpdateTarget();
	UFUNCTION()
	void F_CallClearTargetIndicator();
	void F_Attack();
	void F_Hit(const UPrimitiveComponent* pOverlappedComp);
	void F_ApplyHitDamage(float fDamage, const FVector* pImactPointVector);
	void F_RotateToFacePlayer();
	void F_SetWalkSpeed(float Speed);
	void F_SetWeaponAttackAvailable(EAttackHand AttackType, bool IsAttackAvailable);
	void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted);

public:
	void F_SetSpawner(AMonsterSpawner* Spawner);

public:
	FORCEINLINE AGameMgr* F_GetGameMgr() const { return m_pGameMgr; }
	FORCEINLINE FText* F_GetMonsterName() { return &m_MonsterName; }
	FORCEINLINE UMonsterStatusComponent* F_GetMonsterStatusComponent() const { return MonsterStatusComponent; }
	FORCEINLINE UMonsterSkillsComponent* F_GetMonsterSkillsComponent() const { return MonsterSkillsComponent; }
	FORCEINLINE USceneComponent* F_GetSceneStoneObject() const { return Scene_StoneObject; }
	FORCEINLINE AWeapon_Base* F_GetLeftWeapon() const { return m_LeftWeapon; }
	FORCEINLINE AWeapon_Base* F_GetRightWeapon() const { return m_RightWeapon; }
	FORCEINLINE float F_GetPatrolSpeed() const { return m_PatrolSpeed; }
	FORCEINLINE float F_GetChaseSpeed() const { return m_ChaseSpeed; }
	FORCEINLINE UParticleSystem* F_GetAttackImpact() const { return m_AttackImpact; }

public:
	FDele_Single DELE_TargetStatusBarUpdate;
	FDele_Single DELE_TargetStatusBarMiniUpdate;
	FDele_Multi DELE_TargetDeath;
	FDele_Multi DELE_AttackEnd;
	FOnMontageEnded DELE_MontageEnd;
};
