// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillSlot.h"
#include "Widget/DragIcon.h"
#include "Widget/SlotDragDropOperation.h"
#include "Widget/SkillWindow.h"
#include "Widget/SkillToolTip.h"
#include "Widget/QuickSlotWindow.h"
#include "Widget/QuickSlot.h"
#include "Widget/HeadsUpDisplay.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Manager/GameMgr.h"
#include "Manager/SkillManager.h"
#include "Manager/WidgetManager.h"
#include "Player/TestCpp1Character.h"
#include "Skill/Skill_Base.h"
#include "ActorComponent/PlayerSkillsComponent.h"
#include "ActorComponent/PlayerStatusComponent.h"


USkillSlot::USkillSlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), m_nSkillWindowIndex{}, m_pSkillData{}, m_bPurchased{}
{
}

void USkillSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr->F_GetWidgetMgr()->DELE_UpdateSkillSlotIconTint.AddUFunction(this, FName("F_CallUpdateSkillSlotIconTint"));
	m_eSlotType = ESlotType::E_SkillSlot;
	W_SkillToolTip = m_pGameMgr->F_GetWidgetMgr()->F_GetBPSkillToolTip();
	m_SkillToolTip = CreateWidget<USkillToolTip>(GetWorld(), W_SkillToolTip);
	SetToolTip(m_SkillToolTip);
}

FReply USkillSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (m_pSkillData->m_Enable)
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			F_SkillLevelUp();
			return FReply::Handled();
		}
		else if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			if (m_bPurchased)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMouseButtonDown);
				Image_Down->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
			}
			else
			{
				FText AlertText = FText::FromString(FString::Printf(TEXT("스킬이 활성화되어 있지 않습니다")));
				m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
				m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
			}
		}
	}
	return FReply::Unhandled();
}

void USkillSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragIcon* pNewDragIcon = CreateWidget<UDragIcon>(this, W_DragIcon);
	pNewDragIcon->F_SetDragImage(Image_Item->Brush.GetResourceObject());
	USlotDragDropOperation* pDragDropOperation = Cast<USlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDropOperation::StaticClass()));
	if (pDragDropOperation)
	{
		pDragDropOperation->DefaultDragVisual = pNewDragIcon;
		pDragDropOperation->F_SetDragBeginSlotType(m_eSlotType);
		pDragDropOperation->F_SetDragBeginIndex(m_nSkillWindowIndex);
		pDragDropOperation->F_SetDragBeginSlot(this);
		OutOperation = pDragDropOperation;
	}
}


void USkillSlot::F_SetSkillSlotIcon()
{
	UTexture2D* Icon = m_pSkillData->m_SkillImage;
	if (!m_pSkillData->m_Enable)
	{
		Image_Item->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillIcon"), Icon);
		Image_Item->GetDynamicMaterial()->SetScalarParameterValue(FName("DesaturationValue"), 0.0f);
	}
	else
	{
		Image_Item->GetDynamicMaterial()->SetTextureParameterValue(FName("SkillIcon"), Icon);
		Image_Item->GetDynamicMaterial()->SetScalarParameterValue(FName("DesaturationValue"), 1.0f);
	}
}

void USkillSlot::F_CallUpdateSkillSlotIconTint()
{
	bool bSkillPrerequisite = F_CheckSkillPrerequisite();
	bool bSkillPoint = m_Player->F_GetPlayerStatusComponent()->F_GetSkillPoint() >= m_pSkillData->m_SkillPoint;
	if (m_pSkillData->m_Enable)
	{
		uint8 nCurrentSkillLevel{};
		F_CheckSkillLevel(nCurrentSkillLevel);
		if (bSkillPrerequisite && bSkillPoint && (m_pSkillData->m_MaxSkillLevel> nCurrentSkillLevel))
		{
			Image_Item->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			Image_Item->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}	
}

void USkillSlot::F_SkillLevelUp()
{
	bool bRequirement = F_CheckSkillPrerequisite();
	uint8 nCurrentSkillLevel{};
	F_CheckSkillLevel(nCurrentSkillLevel);
	if (bRequirement)
	{
		if (nCurrentSkillLevel < m_pSkillData->m_MaxSkillLevel)
		{
			uint8 nCurrentPlayerSkillPoint = m_Player->F_GetPlayerStatusComponent()->F_GetSkillPoint();
			if (nCurrentPlayerSkillPoint >= m_pSkillData->m_SkillPoint)
			{
				if (nCurrentSkillLevel == 0)
				{
					UGameplayStatics::PlaySound2D(GetWorld(), m_SoundSkillUpFirst);
				}
				else
				{
					UGameplayStatics::PlaySound2D(GetWorld(), m_SoundSkillUp);
				}
				m_Player->F_GetPlayerStatusComponent()->F_SetSkillPoint(nCurrentPlayerSkillPoint - m_pSkillData->m_SkillPoint);
				m_pGameMgr->F_GetWidgetMgr()->F_GetSkillWindow()->F_CallUpdateSkillPoints();
				m_Player->F_GetPlayerSkillsComponent()->F_AddSkill(m_pSkillData->m_SkillName);
				Image_Item->GetDynamicMaterial()->SetScalarParameterValue(FName("DesaturationValue"), 0.0f);
				m_bPurchased = true;
				if (m_pGameMgr->F_GetWidgetMgr()->DELE_UpdateSkillSlotIconTint.IsBound())
				{
					m_pGameMgr->F_GetWidgetMgr()->DELE_UpdateSkillSlotIconTint.Broadcast();
				}
				m_SkillToolTip->F_SetCurrentSkillLevel(nCurrentSkillLevel + 1);
				m_SkillToolTip->F_UpdateToolTip();
			}
			else
			{
				FText AlertText = FText::FromString(FString::Printf(TEXT("스킬 포인트가 부족합니다")));
				m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
				m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
			}
		}
		else
		{
			FText AlertText = FText::FromString(FString::Printf(TEXT("스킬을 더 이상 올릴 수 없습니다")));
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
			m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
		}
	}
	else
	{
		FText AlertText = FText::FromString(FString::Printf(TEXT("스킬을 올리기 위한 조건을 충족시키세요")));
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
		m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
	}
}

bool USkillSlot::F_CheckSkillPrerequisite()
{
	if (m_pSkillData->m_PreRequisiteSkillName != FName())
	{
		uint8 CurrentPreRequisiteSkillLevel{};
		bool Success = m_Player->F_GetPlayerSkillsComponent()->F_QuerySkill(m_pSkillData->m_PreRequisiteSkillName, CurrentPreRequisiteSkillLevel);
		if (Success && (CurrentPreRequisiteSkillLevel >= m_pSkillData->m_PreRequisiteSkillLevel))
		{
			m_SkillToolTip->F_RemoveRestrictionText();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void USkillSlot::F_CheckSkillLevel(uint8& CurrentSkillLevel)
{
	m_Player->F_GetPlayerSkillsComponent()->F_QuerySkill(m_pSkillData->m_SkillName, CurrentSkillLevel);
}

void USkillSlot::F_CallStartCooldown()
{
	GetWorld()->GetTimerManager().SetTimer(m_CooldownTimerHandle, this, &USkillSlot::EndCooldown, m_pSkillData->m_CoolDownTime, false);
	UpdateQuickSlotCooldownTime();
}

void USkillSlot::UpdateQuickSlotCooldownTime()
{
	EQuickSlotNumber eQuickSlotNumber{};
	uint8 nPairQuickSlotIndex{};
	UQuickSlot* PairQuickSlot{};

	eQuickSlotNumber = m_pGameMgr->F_GetSkillMgr()->F_GetQuickSlotMapValue(m_nSkillWindowIndex);
	if (eQuickSlotNumber != EQuickSlotNumber::E_Default)
	{
		nPairQuickSlotIndex = (uint8)eQuickSlotNumber - 1;
		PairQuickSlot = (*m_pGameMgr->F_GetWidgetMgr()->F_GetQuickSlotWindow()->F_GetQuickSlotArray())[nPairQuickSlotIndex];
		PairQuickSlot->F_UpdateQuickSlotCooldownTime();
	}
}

void USkillSlot::EndCooldown()
{
	GetWorld()->GetTimerManager().ClearTimer(m_CooldownTimerHandle);
	UpdateQuickSlotCooldownTime();
}

void USkillSlot::F_CallCastInterrupted()
{
	EndCooldown();
}

void USkillSlot::F_BindCooldownTimer(ASkill_Base* Skill)
{
	Skill->DELE_CastSuccess.BindUFunction(this, FName("F_CallStartCooldown"));
	Skill->DELE_CastInterrupted.BindUFunction(this, FName("F_CallCastInterrupted"));
}

void USkillSlot::F_SetSkillWindowIndex(uint8 Index)
{
	m_nSkillWindowIndex = Index;
}

void USkillSlot::F_SetSkillData(FSkillData* SkillData)
{
	m_pSkillData = SkillData;
	m_SkillToolTip->F_SetSkillData(m_pSkillData);
}