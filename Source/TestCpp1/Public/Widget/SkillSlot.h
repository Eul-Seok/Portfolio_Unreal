#pragma once

#include "CoreMinimal.h"
#include "Widget/Slot_Base.h"
#include "Skill/SkillData.h"
#include "SkillSlot.generated.h"

UCLASS()
class TESTCPP1_API USkillSlot : public USlot_Base
{
	GENERATED_BODY()

public:
	USkillSlot(const FObjectInitializer& ObjectInitializer);

protected:
	uint8 m_nSkillWindowIndex;
	FSkillData* m_pSkillData;
	UPROPERTY()
	TSubclassOf<class USkillToolTip> W_SkillToolTip;
	UPROPERTY()
	class USkillToolTip* m_SkillToolTip;
	bool m_bPurchased;
	FTimerHandle m_CooldownTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* m_SoundSkillUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* m_SoundSkillUpFirst;

protected:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

protected:
	void UpdateQuickSlotCooldownTime();
	void EndCooldown();

public:
	void F_SetSkillSlotIcon();
	UFUNCTION()
	void F_CallUpdateSkillSlotIconTint();
	void F_SkillLevelUp();
	bool F_CheckSkillPrerequisite();
	void F_CheckSkillLevel(uint8& CurrentSkillLevel);
	UFUNCTION()
	void F_CallStartCooldown();
	UFUNCTION()
	void F_CallCastInterrupted();
	void F_BindCooldownTimer(ASkill_Base* Skill);

public:
	void F_SetSkillWindowIndex(uint8 Index);
	void F_SetSkillData(FSkillData* SKillData);

public:
	FSkillData* F_GetSkillData();
	bool F_GetbPurchased();
	FTimerHandle* F_GetCooldownTimerHandle();
};
