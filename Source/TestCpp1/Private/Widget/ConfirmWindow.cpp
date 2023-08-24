

#include "Widget/ConfirmWindow.h"
#include "Components/Button.h"
#include "Manager/GameMgr.h"
#include "Kismet/GameplayStatics.h"

UConfirmWindow::UConfirmWindow(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void UConfirmWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_pGameMgr = GetWorld() != nullptr ?
	GetWorld()->GetGameState<AGameMgr>() : nullptr;
	Button_Yes->OnClicked.AddDynamic(this, &UConfirmWindow::OnButtonYesClicked);
	Button_No->OnClicked.AddDynamic(this, &UConfirmWindow::OnButtonNoClicked);
}

void UConfirmWindow::OnButtonYesClicked()
{
	DELE_ButtonYes.ExecuteIfBound();
	DELE_ButtonYes.Unbind();
	SetVisibility(ESlateVisibility::Hidden);
}

void UConfirmWindow::OnButtonNoClicked()
{
	DELE_ButtonYes.Unbind();
	SetVisibility(ESlateVisibility::Hidden);
	m_pGameMgr->F_GetSoundMgr()->F_PlaySound(EPlaySound::E_SoundDoNotUse);
}

void UConfirmWindow::F_SetInventoryIndex(uint8 InventoryIndex)
{
	m_nInventoryIndex = InventoryIndex;
}

