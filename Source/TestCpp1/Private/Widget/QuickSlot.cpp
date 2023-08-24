// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlot.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/DragIcon.h"
#include "Widget/SlotDragDropOperation.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/InventorySlot.h"
#include "Widget/SkillSlot.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Manager/InventoryManager.h"
#include "Manager/ItemManager.h"
#include "Manager/SkillManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/TestCpp1Character.h"
#include "Skill/Skill_Base.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"


UQuickSlot::UQuickSlot(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UQuickSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_eSlotType = ESlotType::E_QuickSlot;
	F_ResetQuickSlot();
}

FReply UQuickSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (m_sQuickSlotData.m_bRegistration)
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			F_QuickUse();
			return FReply::Handled();
		}
		Image_Down->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMouseButtonDown);
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return FReply::Unhandled();
	}
}

void UQuickSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragIcon* pNewDragIcon = CreateWidget<UDragIcon>(this, W_DragIcon);
	pNewDragIcon->m_pDragImage = Image_Item->Brush.GetResourceObject();
	USlotDragDropOperation* pDragDropOperation = Cast<USlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDropOperation::StaticClass()));
	if (pDragDropOperation)
	{
		pDragDropOperation->DefaultDragVisual = pNewDragIcon;
		pDragDropOperation->m_eDragBeginSlotType = m_eSlotType;
		pDragDropOperation->m_nDragBeginIndex = m_nQuickSlotIndex;
		pDragDropOperation->m_pDragBeginSlot = this;
		OutOperation = pDragDropOperation;
	}
}

bool UQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	bool bSucess{};
	uint8 nDragBeginIndex{};
	USlotDragDropOperation* Operation = Cast<USlotDragDropOperation>(InOperation);
	nDragBeginIndex = Operation->m_nDragBeginIndex;
	if (Operation->m_eDragBeginSlotType == ESlotType::E_QuickSlot)
	{
		m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_QuickSlotDataSwap(m_nQuickSlotIndex, nDragBeginIndex);
		Operation->m_pDragBeginSlot->Image_Down->SetVisibility(ESlateVisibility::Hidden);
		Image_Down->SetVisibility(ESlateVisibility::Hidden);
		bSucess = true;
		return bSucess;
	}
	else
	{
		EQuickSlotNumber ePairQuickSlotNumber{};
		if (Operation->m_eDragBeginSlotType == ESlotType::E_InventorySlot)
		{
			ePairQuickSlotNumber = m_pGameMgr->F_GetInventoryMgr()->F_GetQuickSlotMapValue(nDragBeginIndex);
		}
		else if (Operation->m_eDragBeginSlotType == ESlotType::E_SkillSlot)
		{
			ePairQuickSlotNumber = m_pGameMgr->F_GetSkillMgr()->F_GetQuickSlotMapValue(nDragBeginIndex);
		}
		if (ePairQuickSlotNumber != EQuickSlotNumber::E_Default)
		{
			TArray<UQuickSlot*>* arQuickSlot = m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_GetQuickSlotArray();
			uint8 nPairQuickSlotIndex = (uint8)ePairQuickSlotNumber - 1;
			
			(*arQuickSlot)[nPairQuickSlotIndex]->F_QuickSlotRegistrationCancle();
		}
		bSucess = F_QuickSlotRegistration(Operation->m_eDragBeginSlotType, Operation->m_nDragBeginIndex);
	}
	Operation->m_pDragBeginSlot->Image_Down->SetVisibility(ESlateVisibility::Hidden);
	Image_Down->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundDrop);
	return bSucess;
}

void UQuickSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (CooldownBar->IsVisible() && m_sQuickSlotData.m_pCooldownTimerHandle->IsValid())
	{
		float ElapsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(*(m_sQuickSlotData.m_pCooldownTimerHandle));
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(*(m_sQuickSlotData.m_pCooldownTimerHandle));
		float InPercent = UKismetMathLibrary::NormalizeToRange(RemainingTime, 0.0f, ElapsedTime + RemainingTime);
		CooldownBar->SetPercent(InPercent);
	}
}

void UQuickSlot::F_UpdateQuickSlotCooldownTime()
{
	m_sQuickSlotData.m_pCooldownTimerHandle = (*m_pGameMgr->F_GetSkillMgr()->F_GetSkillSlotArray())[m_sQuickSlotData.m_nPairSlotIndex]->F_GetCooldownTimerHandle();
	if (m_sQuickSlotData.m_pCooldownTimerHandle)
	{
		if (m_sQuickSlotData.m_pCooldownTimerHandle->IsValid())
		{
			m_sQuickSlotData.m_bCooldown = true;
			F_UpdateCooldownAppearance();
		}
		else
		{
			m_sQuickSlotData.m_bCooldown = false;
			F_UpdateCooldownAppearance();
		}
	}
}

void UQuickSlot::F_QuickUse()
{
	if (m_sQuickSlotData.m_bRegistration)
	{
		if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_InventorySlot)
		{
			m_pGameMgr->F_GetItemMgr()->F_ItemUse(m_sQuickSlotData.m_nPairSlotIndex);
		}
		else if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_SkillSlot)
		{
			if (!m_sQuickSlotData.m_bCooldown && !m_Player->F_GetbPlayingMontage() && m_Player->F_CheckMana(m_sQuickSlotData.m_pQuickSlotSkillData->m_Cost))
			{
				m_pGameMgr->F_GetSkillMgr()->F_UseSkill(m_sQuickSlotData.m_nPairSlotIndex);
			}
			else
			{
				FText AlertText = FText::FromString(FString::Printf(TEXT("스킬을 사용할 수 없습니다")));
				m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
				m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
			}
		}
	}
}

bool UQuickSlot::F_QuickSlotRegistration(ESlotType PairSlotType, uint8 PairSlotIndex)
{
	F_ResetQuickSlot();
	m_sQuickSlotData.m_ePairSlotType = PairSlotType;
	m_sQuickSlotData.m_nPairSlotIndex = PairSlotIndex;
	if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_InventorySlot)
	{	
		FItemData* pItemData = (*m_pGameMgr->F_GetInventoryMgr()->F_GetInventorySlotArray())[m_sQuickSlotData.m_nPairSlotIndex]->F_GetItemData();
		if (pItemData->m_ItemType == EItemType::E_Quest)
		{
			F_ResetQuickSlot();
			F_UpdateQuickSlotIcon();
			FText AlertText = FText::FromString(FString::Printf(TEXT("퀘스트 관련 아이템은 등록할 수 없습니다")));
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
			m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
			return false;
		}
		m_sQuickSlotData.m_pQuickSlotItemData = pItemData;
		m_pGameMgr->F_GetInventoryMgr()->F_SetQuickSlotMap(m_sQuickSlotData.m_nPairSlotIndex, m_eQuickSlotNumber);
	}
	else if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_SkillSlot)
	{
		FSkillData* pSkillData = (*m_pGameMgr->F_GetSkillMgr()->F_GetSkillSlotArray())[m_sQuickSlotData.m_nPairSlotIndex]->F_GetSkillData();
		m_sQuickSlotData.m_pQuickSlotSkillData = pSkillData;
		m_pGameMgr->F_GetSkillMgr()->F_SetQuickSlotMap(m_sQuickSlotData.m_nPairSlotIndex, m_eQuickSlotNumber);
		F_UpdateQuickSlotCooldownTime();
	}
	m_sQuickSlotData.m_bRegistration = true;
	F_UpdateQuickSlotIcon();
	return true;
}

void UQuickSlot::F_QuickSlotRegistrationCancle()
{
	if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_InventorySlot)
	{
		m_pGameMgr->F_GetInventoryMgr()->F_SetQuickSlotMap(m_sQuickSlotData.m_nPairSlotIndex, EQuickSlotNumber::E_Default);
	}
	else if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_SkillSlot)
	{
		m_pGameMgr->F_GetSkillMgr()->F_SetQuickSlotMap(m_sQuickSlotData.m_nPairSlotIndex, EQuickSlotNumber::E_Default);
	}

	F_ResetQuickSlot();
	F_UpdateQuickSlotIcon();
}

void UQuickSlot::F_UpdateQuickSlotIcon()
{
	UTexture2D* Icon = m_sQuickSlotData.m_pQuickSlotItemData->m_ItemImage;
	if (m_sQuickSlotData.m_ePairSlotType == ESlotType::E_SkillSlot)
	{
		Icon = m_sQuickSlotData.m_pQuickSlotSkillData->m_SkillImage;
	}	
	Image_Item->SetBrushFromTexture(Icon);
}

void UQuickSlot::F_ResetQuickSlot()
{
	m_sQuickSlotData.m_pQuickSlotItemData = m_pGameMgr->F_GetInventoryMgr()->F_GetItemDataDefault();
	m_sQuickSlotData.m_pQuickSlotSkillData = m_pGameMgr->F_GetSkillMgr()->F_GetSkillDataDefault();
	m_sQuickSlotData.m_ePairSlotType = ESlotType::E_Default;
	m_sQuickSlotData.m_nPairSlotIndex = 0;
	m_sQuickSlotData.m_bRegistration = false;
	m_sQuickSlotData.m_pCooldownTimerHandle = nullptr;
	m_sQuickSlotData.m_bCooldown = false;
	F_UpdateCooldownAppearance();
}

void UQuickSlot::F_UpdateCooldownAppearance()
{
	if (m_sQuickSlotData.m_bCooldown)
	{
		CooldownBar->SetVisibility(ESlateVisibility::Visible);
		CooldownBar->SetPercent(1.0f);
	}
	else
	{
		CooldownBar->SetVisibility(ESlateVisibility::Hidden);
		CooldownBar->SetPercent(0.0f);
	}
}

void UQuickSlot::F_SetQuickSlotNumber(EQuickSlotNumber QuickSlotNumber)
{
	m_eQuickSlotNumber = QuickSlotNumber;
}

void UQuickSlot::F_SetQuickSlotIndex(uint8 QuickSlotIndex)
{
	m_nQuickSlotIndex = QuickSlotIndex;
}

void UQuickSlot::F_SetQuickSlotData(S_QUICKSLOTDATA* pQuickSlotData)
{
	m_sQuickSlotData = *pQuickSlotData;
}
