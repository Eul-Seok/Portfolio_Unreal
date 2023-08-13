// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BuffPanel.h"
#include "Components/WrapBox.h"
#include "Skill/Skill_Buff.h"
#include "Widget/BuffIcon.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"

UBuffPanel::UBuffPanel(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UBuffPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	W_BuffIcon = m_pGameMgr->F_GetWidgetMgr()->F_GetBPBuffIcon();
}

void UBuffPanel::F_AddBuff(ASkill_Buff* BuffSkill)
{
	UBuffIcon* pNewBuffIcon = CreateWidget<UBuffIcon>(this, W_BuffIcon);
	BuffPanel->AddChildToWrapBox(pNewBuffIcon);
	pNewBuffIcon->F_SetBuffSkillInfo(BuffSkill);
}

void UBuffPanel::F_ClearPanel()
{
	BuffPanel->ClearChildren();
}

