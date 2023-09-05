// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillData.h"
#include "Widget/Slot_Base.h"
#include "Widget/QuickSlotNumber.h"
#include "Widget/QuickSlotData.h"
#include "QuickSlot.generated.h"

UCLASS()
class TESTCPP1_API UQuickSlot : public USlot_Base
{
	GENERATED_BODY()

public:
	UQuickSlot(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CooldownBar;

	/*struct S_QUICKSLOTDATA
	{
		FItemData* m_pQuickSlotItemData;
		FSkillData* m_pQuickSlotSkillData;
		ESlotType m_ePairSlotType;
		uint8 m_nPairSlotIndex;
		bool m_bRegistration;
		bool m_bCooldown;
		FTimerHandle* m_pCooldownTimerHandle;
	};*/
	
protected:
	EQuickSlotNumber m_eQuickSlotNumber;
	uint8 m_nQuickSlotIndex;
	FQuickSlotData m_sQuickSlotData;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	void F_UpdateQuickSlotCooldownTime();
	void F_QuickUse();
	bool F_QuickSlotRegistration(ESlotType PairSlotType, uint8 PairSlotIndex);
	void F_QuickSlotRegistrationCancle();
	void F_UpdateQuickSlotIcon();
	void F_ResetQuickSlot();
	void F_UpdateCooldownAppearance();

public:
	void F_SetQuickSlotNumber(EQuickSlotNumber QuickSlotNumber);
	void F_SetQuickSlotIndex(uint8 QuickSlotIndex);
	void F_SetQuickSlotData(FQuickSlotData* pQuickSlotData);
	
public:
	FORCEINLINE UProgressBar* F_GetCooldownBar() const { return CooldownBar; }
	FORCEINLINE EQuickSlotNumber F_GetQuickSlotNumber() const { return m_eQuickSlotNumber; }
	FORCEINLINE uint8 F_GetQuickSlotIndex() const { return m_nQuickSlotIndex; }
	FORCEINLINE FQuickSlotData* F_GetQuickSlotData() { return &m_sQuickSlotData; }
};
