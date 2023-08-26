
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget/QuickSlotNumber.h"
#include "QuickSlotWindow.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FDele_Multi_TwoParams, uint8, EQuickSlotNumber);

class UQuickSlot;
class USlot_Base;

UCLASS()
class TESTCPP1_API UQuickSlotWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuickSlotWindow(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Slot;

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	TArray<UQuickSlot*> m_arQuickSlot;
	UPROPERTY()
	TSubclassOf<USlot_Base> W_QuickSlot;

protected:
	virtual void NativeOnInitialized() override;

private:
	void CreateQuickSlot(uint8 Row, uint8 Column);

public:
	void F_QuickSlotUse(uint8 QuickSlotIndex);
	void F_QuickSlotDataSwap(uint8 Dst, uint8 Src);
	TArray<UQuickSlot*>* F_GetQuickSlotArray();

public:
	UFUNCTION()
	void F_CallResetQuickSlot(uint8 PairIndex);
	
	FDele_Multi_TwoParams DELE_QuickSlotConnectionChange;
};
