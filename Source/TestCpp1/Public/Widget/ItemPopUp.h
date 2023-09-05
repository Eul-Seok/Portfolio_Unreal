// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPopUp.generated.h"

UCLASS()
class TESTCPP1_API UItemPopUp : public UUserWidget
{
	GENERATED_BODY()

public:
	UItemPopUp(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Use;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Drop;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Destroy;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* UseButtonText;
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	uint8 m_InventoryIndex;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void OnButtonUseClicked();
	UFUNCTION()
	void OnButtonDropClicked();
	UFUNCTION()
	void OnButtonDestroyClicked();
	UFUNCTION()
	void CallItemDestroy();

public:
	void F_SetInventoryIndex(uint8 Index);
	void F_SetItemPopUpInfo(EItemType ItemType);
};
