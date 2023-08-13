// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item/Weapon_Base.h"

UItemToolTip::UItemToolTip(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UItemToolTip::F_SetItemData(FItemData* ItemData)
{
	if (ItemData->m_ItemType == EItemType::E_Default)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		m_pItemData = ItemData;
		Image_ItemIcon->SetBrushFromTexture(m_pItemData->m_ItemImage);
		Text_ItemName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *m_pItemData->m_ItemName.ToString())));
		if (ItemData->m_ItemType == EItemType::E_Consumption)
		{
			Text_ItemType->SetText(FText::FromString(FString::Printf(TEXT("소모 아이템"))));
			Text_ItemAffectValue->SetText(FText::FromString(FString::Printf(TEXT("회복량: %.0f"), m_pItemData->m_fAffectValue)));
		}
		else if (ItemData->m_ItemType == EItemType::E_Equipment)
		{
			Text_ItemType->SetText(FText::FromString(FString::Printf(TEXT("장비 아이템"))));
			Text_ItemAffectValue->SetText(FText::FromString(FString::Printf(TEXT("공격력: %.0f"), Cast<AWeapon_Base>(m_pItemData->m_ItemClass.GetDefaultObject())->F_GetWeaponDamage())));
		}
		else if (ItemData->m_ItemType == EItemType::E_Quest)
		{
			Text_ItemType->SetText(FText::FromString(FString::Printf(TEXT("퀘스트 아이템"))));
			Text_ItemAffectValue->SetText(FText::FromString(FString::Printf(TEXT(""))));
		}

		Text_Description->SetText(m_pItemData->m_ItemDescription);
	}
}

