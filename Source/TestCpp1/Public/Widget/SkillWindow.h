// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skill/SkillData.h"
#include "SkillWindow.generated.h"

class USkillSlot;
class USlot_Base;

UCLASS()
class TESTCPP1_API USkillWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USkillWindow(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTitleBar* W_TitleBar;
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_KatanaSkillSlot;
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_CommonSkillSlot;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillPointsText;

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class ATestCpp1Character* m_Player;
	UPROPERTY()
	uint8 m_nSkillWeaponTypeCount = 2;
	UPROPERTY()
	TArray<USkillSlot*> m_arSkillSlot;
	UPROPERTY()
	TSubclassOf<USlot_Base> W_SkillSlot;
	FSkillData* m_SkillDataDefault;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

protected:
	void CreateSkillSlotArray(TArray<USkillSlot*>* arSkillSlot, uint8 nLength, uint8 nColumn);
	USkillSlot* CreateSkillSlot(UUniformGridPanel* UniformGirdPanel, uint8 nRow, uint8 nColumn);

public:
	UFUNCTION()
	void F_CallUpdateSkillPoints();

public:
	FORCEINLINE TArray<USkillSlot*>* F_GetarSkillSlot() { return &m_arSkillSlot; }
};
