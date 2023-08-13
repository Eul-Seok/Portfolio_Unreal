// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMethodWindow.generated.h"

UCLASS()
class TESTCPP1_API UGameMethodWindow : public UUserWidget
{
	GENERATED_BODY()
		
public:
	UGameMethodWindow(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_GameMethod;
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Method;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Before;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Next;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Page;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_CloseGameMethod;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> m_arMethodImage;
	uint8 m_nImageIndex;

protected:
	UFUNCTION()
	void HiddenGameMethodWindow();
	void UpdateMethodImage(uint8 nIndex);

	UFUNCTION()
	void OnButtonClicked_Before();
	UFUNCTION()
	void OnButtonClicked_Next();

public:
	void F_DisplayGameMethodWindow();
	
};
