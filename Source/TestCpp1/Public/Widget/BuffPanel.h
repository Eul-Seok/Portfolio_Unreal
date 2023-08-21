// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffPanel.generated.h"

class UBuffIcon;
class ASkill_Buff;

UCLASS()
class TESTCPP1_API UBuffPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UBuffPanel(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* BuffPanel;

protected:
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	TSubclassOf<UBuffIcon> W_BuffIcon;

public:
	void F_AddBuff(ASkill_Buff* BuffSkill);
	void F_ClearPanel();
};
