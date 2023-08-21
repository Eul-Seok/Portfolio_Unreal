
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemData.h"
#include "Inventory.generated.h"

class USlot_Base;

UCLASS()
class TESTCPP1_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventory(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTitleBar* W_TitleBar;
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Slot;
	
protected:
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	TArray<class UInventorySlot*> m_arInventorySlot;
	UPROPERTY()
	TSubclassOf<USlot_Base> W_InventorySlot;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

private:
	void CreateInventorySlot(uint8 Row, uint8 Column);

public:
	TArray<UInventorySlot*>* F_GetarInventorySlot();
};
