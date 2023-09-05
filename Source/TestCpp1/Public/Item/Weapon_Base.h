// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon_Base.generated.h"

UCLASS()
class TESTCPP1_API AWeapon_Base : public AItem
{
	GENERATED_BODY()
	
public:
	AWeapon_Base();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* TrailParticleSystemComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* m_SoundMonsterHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> m_setHitObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fWeaponDamage;
	bool m_bKnockBackAttack;
	bool m_bStunAttack;

public:
	void F_SetAttackAvailable(bool IsAvailable);
	void F_BeginTrail(float TrailWidth);
	void F_EndTrail();

public:
	void F_SetbKnockBackAttack(bool IsKnockBack);
	void F_SetbStunAttack(bool IsStun);

public:
	FORCEINLINE USoundBase* F_GetSoundMonsterHit() const { return m_SoundMonsterHit; }
	FORCEINLINE UParticleSystemComponent* F_GetTrail() const { return TrailParticleSystemComponent; }
	FORCEINLINE float F_GetWeaponDamage() const { return m_fWeaponDamage; }

protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
