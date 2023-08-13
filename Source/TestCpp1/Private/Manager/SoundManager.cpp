// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

USoundManager::USoundManager()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_OPENUI(TEXT("/Game/Sound/Cue/Cue_OpenUI"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_ITEMPICKUP(TEXT("/Game/Sound/Cue/Cue_ItemPickUp"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_ITEMDROP(TEXT("/Game/Sound/Cue/Cue_ItemDrop"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_ITEMDESTROY(TEXT("/Game/Sound/Cue/Cue_ItemDestroy"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_DRINK(TEXT("/Game/Sound/Cue/Cue_Drink"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_DONOTUSE(TEXT("/Game/Sound/Cue/Cue_DoNotUse"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_LEVELUP(TEXT("/Game/Sound/Cue/Cue_LevelUp"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_QUESTACCEPT(TEXT("/Game/Sound/Cue/Cue_QuestAccept"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_QUESTSINGLEOBJECTIVECOMPLETE(TEXT("/Game/Sound/Cue/Cue_QuestSingleObjectiveComplete"));
	static ConstructorHelpers::FObjectFinder<USoundBase> CUE_QUESTCOMPLETE(TEXT("/Game/Sound/Cue/Cue_QuestComplete"));

	m_arSound.Reserve((uint8)EPlaySound::E_PlaySound_Max);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_Default, nullptr);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundOpenUI, CUE_OPENUI.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundItemPickUp, CUE_ITEMPICKUP.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundItemDrop, CUE_ITEMDROP.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundItemDestroy, CUE_ITEMDESTROY.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundDrink, CUE_DRINK.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundDoNotUse, CUE_DONOTUSE.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundLevelUp, CUE_LEVELUP.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundQuestAccept, CUE_QUESTACCEPT.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundQuestSingleObjectiveComplete, CUE_QUESTSINGLEOBJECTIVECOMPLETE.Object);
	m_arSound.EmplaceAt((uint8)EPlaySound::E_SoundQuestComplete, CUE_QUESTCOMPLETE.Object);
}


void USoundManager::F_PlaySound(EPlaySound Sound)
{
	USoundBase* PlaySound = m_arSound[(int)Sound];
	if (PlaySound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PlaySound);
	}
}
