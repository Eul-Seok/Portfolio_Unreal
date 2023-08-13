// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Quest/Quest.h"
#include "Quest/QuestLog.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene_InteractBox = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_InteractBox"));
	Scene_InteractBox->SetupAttachment(GetMesh(), FName("pelvis"));

	InteractBoxCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractBoxCollision"));
	InteractBoxCollision->SetupAttachment(Scene_InteractBox);

	Scene_TextRender = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_TextRender"));
	Scene_TextRender->SetupAttachment(RootComponent);

	TextRenderHasQuest = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderHasQuest"));
	TextRenderHasQuest->SetupAttachment(Scene_TextRender);
	TextRenderNPCName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderNPCName"));
	TextRenderNPCName->SetupAttachment(Scene_TextRender);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	GetAttachedActors(m_arQuestActor);
	DELE_UpdateTextRenderHasQuest.AddUFunction(this, FName("F_CallUpdateTextRenderHasQuest"));
	F_CallUpdateTextRenderHasQuest();
	m_RotationDefault = GetActorRotation();
	TextRenderNPCName->SetText(m_Name);
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateTextRenderRotation(TextRenderNPCName);
	if (TextRenderHasQuest->IsVisible())
	{
		UpdateTextRenderRotation(TextRenderHasQuest);
	}
}

bool ANPC::CheckPreRequisiteQuest(AQuest* Quest)
{
	bool bSatisfied{};
	bSatisfied = true;
	AQuest* PreRequisiteQuest = Quest->F_GetPreRequisiteQuest();
	if (PreRequisiteQuest)
	{
		if (!PreRequisiteQuest->F_GetbComplete())
		{
			bSatisfied = false;
		}
	}
	return bSatisfied;
}

bool ANPC::CanDisplayQuest()
{
	bool bDisplay{};
	bDisplay = false;
	if (m_nCurrentQuestIndex < m_arQuestActor.Num())
	{
		AQuest* Quest = Cast<AQuest>(m_arQuestActor[m_nCurrentQuestIndex]);
		if (!Quest->F_GetbComplete() && CheckPreRequisiteQuest(Quest))
		{
			bDisplay = true;
		}
	}
	return bDisplay;
}

bool ANPC::CheckAcceptQuest()
{
	bool bAccept{};
	if (m_nCurrentQuestIndex < m_arQuestActor.Num())
	{
		AQuest* Quest = Cast<AQuest>(m_arQuestActor[m_nCurrentQuestIndex]);
		bAccept = !Quest->F_GetbAccept();
	}
	return bAccept;
}

void ANPC::UpdateTextRenderRotation(UTextRenderComponent* TextRender)
{
	FVector TextRenderLocation = TextRender->GetComponentLocation();
	FVector CameraManagerLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(TextRenderLocation, CameraManagerLocation);
	TextRender->SetWorldRotation(NewRotation);
}

void ANPC::F_CallUpdateTextRenderHasQuest()
{
	if (CanDisplayQuest() && CheckAcceptQuest())
	{
		TextRenderHasQuest->SetVisibility(true);
		AQuest* Quest = Cast<AQuest>(m_arQuestActor[m_nCurrentQuestIndex]);
		if (!Quest->F_GetbStoryQuest())
		{
			TextRenderHasQuest->SetTextRenderColor(FColor::White);
		}
		else
		{
			TextRenderHasQuest->SetTextRenderColor(FColor::Yellow);
		}
	}
	else
	{
		TextRenderHasQuest->SetVisibility(false);
	}
}

void ANPC::F_DisplayQuestContent()
{
	if (CanDisplayQuest())
	{
		AQuest* Quest = Cast<AQuest>(m_arQuestActor[m_nCurrentQuestIndex]);
		m_pGameMgr->F_GetWidgetMgr()->F_ToggleUI(EUIType::E_QuestContent);
		m_pGameMgr->F_GetWidgetMgr()->F_GetQuestContent()->F_SetQuestInfo(Quest);
	}
}

void ANPC::F_InteractionNPC()
{
	UQuestLog* QuestLog = m_pGameMgr->F_GetQuestLogComponent();
	TArray<AQuest*>* arQuest = QuestLog->F_GetarQuest();
	for (uint8 i = 0; i < (*arQuest).Num(); i++)
	{
		(*arQuest)[i]->DELE_InteractionTarget.Broadcast(this);
	}
}

void ANPC::F_QuestComplete()
{
	m_nCurrentQuestIndex++;
}

void ANPC::F_RotateToFacePlayer(AActor* Player)
{
	FVector PlayerLocation = Player->GetActorLocation();
	FVector NPCLocation = GetActorLocation();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(NPCLocation, FVector(PlayerLocation.X, PlayerLocation.Y, NPCLocation.Z)));
}

void ANPC::F_RotationReset()
{
	SetActorRotation(m_RotationDefault);
}

bool ANPC::F_CheckHasQuest()
{
	if (m_arQuestActor.Num())
	{
		m_bHasQuest = true;
	}
	else
	{
		m_bHasQuest = false;
	}
	return m_bHasQuest;
}

void ANPC::F_DisplayTextRenderHasQuest(bool bDisplay)
{
	TextRenderHasQuest->SetVisibility(bDisplay);
}
