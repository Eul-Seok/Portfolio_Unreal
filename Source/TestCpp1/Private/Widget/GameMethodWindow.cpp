// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameMethodWindow.h"
#include "Widget/PauseMenu.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

UGameMethodWindow::UGameMethodWindow(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UGameMethodWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button_Before->OnClicked.AddDynamic(this, &UGameMethodWindow::OnButtonClicked_Before);
	Button_Next->OnClicked.AddDynamic(this, &UGameMethodWindow::OnButtonClicked_Next);
	Button_CloseGameMethod->OnClicked.AddDynamic(this, &UGameMethodWindow::HiddenGameMethodWindow);
	UpdateMethodImage(0);
}

void UGameMethodWindow::HiddenGameMethodWindow()
{
	Panel_GameMethod->SetVisibility(ESlateVisibility::Hidden);
	UPauseMenu* PauseMenu = Cast<UPauseMenu>(GetOuter()->GetOuter());
	if (PauseMenu)
	{
		PauseMenu->F_DisplayMenu();
	}
}

void UGameMethodWindow::UpdateMethodImage(uint8 nIndex)
{
	if (m_arMethodImage.IsValidIndex(nIndex))
	{
		Image_Method->SetBrushFromTexture(Cast<UTexture2D>(m_arMethodImage[nIndex]));
		Text_Page->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), nIndex+1, m_arMethodImage.Num())));

		if (nIndex == 0)
		{
			Button_Before->SetVisibility(ESlateVisibility::Hidden);
			Button_Next->SetVisibility(ESlateVisibility::Visible);
		}
		else if (nIndex == m_arMethodImage.Num() - 1)
		{
			Button_Before->SetVisibility(ESlateVisibility::Visible);
			Button_Next->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			Button_Before->SetVisibility(ESlateVisibility::Visible);
			Button_Next->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UGameMethodWindow::OnButtonClicked_Before()
{
	if (m_nImageIndex >= 0)
	{
		m_nImageIndex--;
		UpdateMethodImage(m_nImageIndex);
	}
}

void UGameMethodWindow::OnButtonClicked_Next()
{
	if (m_nImageIndex < m_arMethodImage.Num())
	{
		m_nImageIndex++;
		UpdateMethodImage(m_nImageIndex);
	}
}

void UGameMethodWindow::F_DisplayGameMethodWindow()
{
	Panel_GameMethod->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

