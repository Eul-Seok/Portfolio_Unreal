

#pragma once

#include "CoreMinimal.h"
#include "Widget/Slot_Base.h"
#include "RewardSlot.generated.h"

class UItemToolTip;

UCLASS()
class TESTCPP1_API URewardSlot : public USlot_Base
{
	GENERATED_BODY()
	

public:
	URewardSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	TSubclassOf<UItemToolTip> W_ItemToolTip;
	UPROPERTY()
	class UItemToolTip* m_pItemToolTip;


protected:
	void CreateToolTip();

public:
	void F_SetItemData(FItemData* pItemData);
};
