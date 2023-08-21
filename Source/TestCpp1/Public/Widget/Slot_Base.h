
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget/SlotType.h"
#include "Item/ItemData.h"
#include "Kismet/GameplayStatics.h"
#include "Slot_Base.generated.h"

class UDragIcon;

UCLASS()
class TESTCPP1_API USlot_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	USlot_Base(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Item;
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Back;
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Over;
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Down;
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_InvenEvent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESlotType m_eSlotType;
	class AGameMgr* m_pGameMgr;
	class ATestCpp1Character* m_Player;
	class APlayerController* m_PlayerController;
	UPROPERTY()
	TSubclassOf<UDragIcon> W_DragIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* m_SoundMouseEnter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* m_SoundMouseButtonDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* m_SoundDrop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* m_SoundDoNotUse;
	

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
