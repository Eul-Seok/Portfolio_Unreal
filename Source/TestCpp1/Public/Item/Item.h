#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ItemData.h"
#include "Item.generated.h"

UCLASS()
class TESTCPP1_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual ~AItem();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* ItemMesh; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* PickUpRange;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* m_pItemDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AGameMgr* m_pGameMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_RowName;
	

protected:
	virtual void BeginPlay() override;

public:
	bool F_ItemGet(class ATestCpp1Character* Character);
	void F_DestroyPickUpRange();
	UStaticMeshComponent* GetStaticMeshComponent();

public:
	FName* F_GetRowName();
};

