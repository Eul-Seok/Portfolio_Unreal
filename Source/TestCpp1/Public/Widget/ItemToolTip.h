// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemData.h"
#include "ItemToolTip.generated.h"


UCLASS()
class TESTCPP1_API UItemToolTip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UItemToolTip(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemIcon;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_ItemName;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_ItemType;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_ItemAffectValue;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Description;

protected:
	FItemData* m_pItemData;

public:
	void F_SetItemData(FItemData* ItemData);

};
