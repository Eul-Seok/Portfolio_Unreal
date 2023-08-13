// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAIController.h"
#include "Monster/Monster.h"
#include "Monster/MonsterState.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Player/TestCpp1Character.h"

const FName AMonsterAIController::Key_Player(TEXT("Player"));
const FName AMonsterAIController::Key_PatrolLocation(TEXT("PatrolLocation"));
const FName AMonsterAIController::Key_MosterState(TEXT("MonsterState"));
const FName AMonsterAIController::Key_Distance(TEXT("Distance"));
const FName AMonsterAIController::Key_bDeath(TEXT("bDeath"));

AMonsterAIController::AMonsterAIController(const FObjectInitializer& ObjectInitializer)
	/*Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))*/
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/Monster_Base/BT_MonsterAI"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Monster/Monster_Base/BB_MonsterAI"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	SetPerceptionSystem();
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		RunBehaviorTree(BTAsset);
		Blackboard->SetValueAsEnum(Key_MosterState, (uint8)EMonsterState::E_Patrol);
	}
	
}

void AMonsterAIController::SetPerceptionSystem()
{	
	AIPerception = CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	AIPerception->ConfigureSense(*SightConfig);
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = 700.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnTargetDetected);
}

void AMonsterAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	if (actor->ActorHasTag(FName("Player")))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetWorld()->GetTimerManager().ClearTimer(m_PerceptionTimer);
			m_Player = Cast<ATestCpp1Character>(actor);
			SetPlayer(m_Player);
			Blackboard->SetValueAsEnum(Key_MosterState, (uint8)EMonsterState::E_Chase);
			AMonster* Monster = Cast<AMonster>(GetPawn());
			Monster->F_SetWalkSpeed(Monster->F_GetChaseSpeed());
			m_DelegateHandle = m_Player->DELE_PlayerDeath.AddUFunction(this, FName("CallResetPlayer"));
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(m_PerceptionTimer, this, &AMonsterAIController::CallResetPlayer, 15.0f, false);
		}	
	}
}

void AMonsterAIController::SetPlayer(AActor* Player)
{
	Blackboard->SetValueAsObject(Key_Player, Player);
}

void AMonsterAIController::CallResetPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(m_PerceptionTimer);
	if (m_Player)
	{
		m_Player->DELE_PlayerDeath.Remove(m_DelegateHandle);
	}
	m_Player = nullptr;
	SetPlayer(nullptr);
	Blackboard->SetValueAsEnum(Key_MosterState, (uint8)EMonsterState::E_Patrol);
	AMonster* Monster = Cast<AMonster>(GetPawn());
	Monster->F_SetWalkSpeed(Monster->F_GetPatrolSpeed());
}
