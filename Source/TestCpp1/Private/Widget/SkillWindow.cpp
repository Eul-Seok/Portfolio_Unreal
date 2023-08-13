// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillWindow.h"
#include "Widget/SkillSlot.h"
#include "Widget/TitleBar.h"
#include "Player/TestCpp1Character.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/SkillManager.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

USkillWindow::USkillWindow(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void USkillWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	uint8 nRow = m_pGameMgr->F_GetSkillMgr()->F_GetRowCount();
	uint8 nColumn = m_pGameMgr->F_GetSkillMgr()->F_GetColumnCount();
	uint8 nLength = nRow * nColumn;
	m_nSkillWeaponTypeCount = ((uint8)ESkillWeaponType::E_SkillWeaponType_Max) - 1;
	W_SkillSlot = m_pGameMgr->F_GetWidgetMgr()->F_GetBPSkillSlot();
	m_SkillDataDefault = m_pGameMgr->F_GetSkillMgr()->F_GetSkillDataDefault();
	CreateSkillSlotArray(&m_arSkillSlot, nLength, nColumn);
	for (uint8 Index = 0; Index < nLength * m_nSkillWeaponTypeCount; Index++)
	{
		m_arSkillSlot[Index]->F_SetSkillWindowIndex(Index);
		m_arSkillSlot[Index]->F_SetSkillData(m_SkillDataDefault);
		m_arSkillSlot[Index]->F_SetSkillSlotIcon();
	}
	F_CallUpdateSkillPoints();
	m_Player->F_GetPlayerStatusComponent()->DELE_LevelUp.AddUFunction(this, FName("F_CallUpdateSkillPoints"));
	W_TitleBar->F_GetTitleTextBlock()->SetText(FText::FromString(FString::Printf(TEXT("스킬창"))));
}

void USkillWindow::NativeDestruct()
{
	Super::NativeDestruct();
	UWidgetBlueprintLibrary::CancelDragDrop();
}

void USkillWindow::CreateSkillSlotArray(TArray<USkillSlot*>* arSkillSlot, uint8 nLength, uint8 nColumn)
{
	(*arSkillSlot).Reserve(nLength * m_nSkillWeaponTypeCount);
	for (uint8 Index = 0; Index < nLength; Index++)
	{
		USkillSlot* NesKatanaSkillSklot = CreateSkillSlot(UniformGridPanel_KatanaSkillSlot, Index / nColumn, Index % nColumn);
		(*arSkillSlot).EmplaceAt(Index, NesKatanaSkillSklot);
		
	}
	for (uint8 Index = nLength; Index < nLength * m_nSkillWeaponTypeCount; Index++)
	{
		USkillSlot* NesCommonSkillSklot = CreateSkillSlot(UniformGridPanel_CommonSkillSlot, (Index - nLength) / nColumn, (Index - nLength) % nColumn);
		(*arSkillSlot).EmplaceAt(Index, NesCommonSkillSklot);
	}
}

USkillSlot* USkillWindow::CreateSkillSlot(UUniformGridPanel* UniformGirdPanel, uint8 nRow, uint8 nColumn)
{
	USkillSlot* pNewSkillSlot = CreateWidget<USkillSlot>(this, W_SkillSlot);
	UniformGirdPanel->AddChildToUniformGrid(pNewSkillSlot, nRow, nColumn);

	return pNewSkillSlot;
}

void USkillWindow::F_CallUpdateSkillPoints()
{
	if (m_Player)
	{
		SkillPointsText->SetText(FText::FromString(FString::Printf(TEXT("스킬 포인트: %d"), m_Player->F_GetPlayerStatusComponent()->F_GetSkillPoint())));
	}
}

TArray<USkillSlot*>* USkillWindow::F_GetarSkillSlot()
{
	return &m_arSkillSlot;
}
