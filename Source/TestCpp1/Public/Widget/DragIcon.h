// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragIcon.generated.h"

/**
 * 
 */
UCLASS()
class TESTCPP1_API UDragIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDragIcon(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* DragIcon;

protected:
	UPROPERTY(EditAnywhere)
	class UObject* m_pDragImage;

public:
	void F_SetDragImage(UObject* DragImage);

public:
	FORCEINLINE UObject* F_GetDragImage() const { return m_pDragImage; }
};
