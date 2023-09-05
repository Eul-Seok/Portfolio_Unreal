// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item/ItemData.h"
#include "Skill/SkillWeaponType.h"
#include "TestCpp1Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

UCLASS(config=Game)
class ATestCpp1Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATestCpp1Character();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_UnequipSword;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_UnequipBow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_WeaponRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* ChildActor_WeaponRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_WeaponLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Scene_HitBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* HitBoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* PickUpBoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* TargetingBoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* InteractBoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerStatusComponent* PlayerStatusComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerSkillsComponent* PlayerSkillsComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	class AGameMgr* m_pGameMgr;
	UPROPERTY(BlueprintReadOnly)
	class AMyPlayerController* m_PlayerController;
	UPROPERTY()
	TSet<class AItem*> m_setOverlapItem;
	uint8 m_nOverlapItemCount;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSet<class AMonster*> m_setOverlapMonster;
	UPROPERTY()
	class ANPC* m_pOverlapNPC;
	UPROPERTY()
	class AWeapon_Base* m_RightHandWeapon;
	UPROPERTY()
	class AWeapon_Base* m_Weapon;
	UPROPERTY()
	bool m_bHasWeapon;
	UPROPERTY()
	bool m_bOneHandWeaponEquippeed;
	UPROPERTY()
	int8 m_nAttackCombo;
	UPROPERTY()
	bool m_bCasting;
	UPROPERTY()
	bool m_bPlayingMontage;
	bool m_bDeath;
	FVector m_TargetActorLocation;
	FTimerHandle m_TimerHandle;
	FTimerHandle m_PlayerRenderCustomDepthTimer;
	FTimerHandle m_PlayerStunTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> m_AnimBlueprintKatana;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> m_AnimBlueprintHand;
	ESkillWeaponType m_CurrentSkillWeaponType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimKatanaDefaultAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimHandDefaultAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimOneHandWeaponEquipped;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimOneHandWeaponUnequipped;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UAnimMontage* m_AnimPlayerDie;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimKnockBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimStun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* m_AttackImpact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* m_SoundHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* m_SoundKnockBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATargetPoint* m_RevivalPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimEvasion_F;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimEvasion_B;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimEvasion_R;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAnimMontage* m_AnimEvasion_L;

	FOnMontageEnded CompleteDelegate;
	FOnMontageEnded CompleteDelegatePlayingMontage;
	FOnMontageEnded CompleteDelegateEquip;
		
protected:
	UFUNCTION()
	void PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted);
	void FunctionToExecuteOnAnimationEndEvasion(UAnimMontage* animMontage, bool bInterrupted);
	void FunctionToExecuteOnAnimationEndEquip(UAnimMontage* animMontage, bool bInterrupted);
	void BindOverapEvent();
	float CalculateHitDamage(const UPrimitiveComponent* pOverlappedComp);
	void PlayerDie();
	void StopStun();
	void ResetPlayingMontage();
	void ResetAttackCombo();
	void ChangeAnimInstance();
	void ResetAnimInstance();
	void RenderCustomDepthOn();
	void RenderCustomDepthOff();

public:
	void F_TargetingModeOn();
	void F_TargetingModeOff();
	void F_CreateWeapon(TSubclassOf<AWeapon_Base> Weapon);
	void F_OneHandWeaponEquipped();
	void F_SetWeaponAttackAvailable(bool IsAttackAvailable);
	void F_DefaultAttack();
	bool F_CheckMana(float ManaCost);
	void F_Hit(const UPrimitiveComponent* pOverlappedComp);
	void F_ApplyHitDamage(float fDamage, const FVector* pHitImactPointVector);
	void F_PlayKnockBack();
	void F_PlayStun(float fDuration = 2.0f);
	void F_Evasion(float Direction);
	void F_Revival();

	void F_OverlapItemAdd(AItem* Item);
	void F_OverlapItemRemove(AItem* Item);
	void F_OverlapMonsterAdd(AMonster* Monster);
	void F_OverlapMonsterRemove(AMonster* Monster);

public:
	void F_SetbOneHandWeaponEquippeed(bool IsEquipped);
	void F_SetbCasting(bool IsCasting);
	void F_SetbPlayingMontage(bool IsPlayingMontage);

public:
	FORCEINLINE UPlayerStatusComponent* F_GetPlayerStatusComponent() const { return PlayerStatusComponent; }
	FORCEINLINE UPlayerSkillsComponent* F_GetPlayerSkillsComponent() const { return PlayerSkillsComponent; }
	FORCEINLINE USceneComponent* F_GetSceneWeaponRigth() const { return Scene_WeaponRight; }
	FORCEINLINE USceneComponent* F_GetSceneUnequipSword() const { return Scene_UnequipSword; }
	FORCEINLINE TSet<AItem*>* F_GetOverLapItem() { return &m_setOverlapItem; }
	FORCEINLINE TSet<AMonster*>* F_GetOverLapMonster() { return &m_setOverlapMonster; }
	FORCEINLINE AWeapon_Base* F_GetRightHandWeapon() const { return m_RightHandWeapon; }
	FORCEINLINE AWeapon_Base* F_GetWeapon() const { return m_Weapon; }
	FORCEINLINE AGameMgr* F_GetGameMgr() const { return m_pGameMgr; }
	FORCEINLINE bool F_GetbCasting() const { return m_bCasting; }
	FORCEINLINE bool F_GetbPlayingMontage() const { return m_bPlayingMontage; }
	FORCEINLINE UParticleSystem* F_GetAttackImpact() const { return m_AttackImpact; }
	FORCEINLINE ANPC* F_GetOverlapNPC() const { return m_pOverlapNPC; }
	FORCEINLINE ESkillWeaponType F_GetCurrentSkillWeaponType() const { return m_CurrentSkillWeaponType; }

protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBeginNPC(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndNPC(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBeginMonster(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndMonster(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FDele_Multi DELE_PlayerDeath;
};

