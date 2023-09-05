// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmWindow.generated.h"

DECLARE_DELEGATE(FDele_Single);

UCLASS()
class TESTCPP1_API UConfirmWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UConfirmWindow(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Yes;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_No;
	
protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	uint8 m_nInventoryIndex;

protected:
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void OnButtonYesClicked();
	UFUNCTION()
	void OnButtonNoClicked();

public:
	void F_SetInventoryIndex(uint8 InventoryIndex);

public:
	FORCEINLINE uint8 F_GetInventoryIndex() const { return m_nInventoryIndex; }

public:
	FDele_Single DELE_ButtonYes;
};
