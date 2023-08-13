
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Interface_Affect.h"
#include "ItemManager.generated.h"

DECLARE_DELEGATE_OneParam(FDele_Single_OneParam, uint8);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTCPP1_API UItemManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UItemManager();

protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class ATestCpp1Character* m_Player;
	IInterface_Affect* m_Interface_Affect;

public:	
	void F_Init();
	bool F_ItemUse(uint8 Index);
	bool F_ItemDrop(uint8 Index);
	bool F_ItemDestroy(uint8 Index);
	bool ApplyAffect(uint8 Index);
	void ItemSpawn(uint8 Index);

	TArray<class UInventorySlot*>* F_GetInventorySlotArray();
	
	FDele_Single_OneParam DELE_InventoryItemDestroy;
};
