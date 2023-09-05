// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestLogEntry.generated.h"

UCLASS()
class TESTCPP1_API UQuestLogEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestLogEntry(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_Active;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Active;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_QuestName;
	
protected:
	UPROPERTY()
	class AGameMgr* m_pGameMgr;
	UPROPERTY()
	class AQuest* m_Quest;
	bool bActive;

protected:
	virtual void NativeOnInitialized() override;

protected:
	void ActiveSlate();
	void InactiveSlate();
	UFUNCTION()
	void CallUpdateActiveSlate();

public:
	void F_SetQuestInfo(AQuest* Quest);
	
protected:
	UFUNCTION()
	void OnButtonActiveClicked();
};
