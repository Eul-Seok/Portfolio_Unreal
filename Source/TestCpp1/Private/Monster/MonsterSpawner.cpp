
#include "Monster/MonsterSpawner.h"
#include "Monster/Monster.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

AMonsterSpawner::AMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SpawnSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnSphere"));
	RootComponent = RootScene;
	SpawnSphere->SetupAttachment(RootScene);
}

void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(m_SpawnTimerHandle, this, &AMonsterSpawner::SpawnerAction, m_fSpawnTimeInterval, m_bSpawnLoop);
}

void AMonsterSpawner::SpawnerAction()
{
	if (m_nMonsterCount < m_nMaxMonsterCount)
	{
		F_MonsterSpawn();
		m_nMonsterCount++;
	}
}

void AMonsterSpawner::F_RemoveMonster()
{
	m_nMonsterCount--;
}

void AMonsterSpawner::F_MonsterSpawn()
{
	UWorld* World = GetWorld();
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NevSystem faild!"));
		return;
	}
	FVector SpawnLocation{};
	FVector Origin = GetActorLocation();
	FNavLocation NextPatrol{};
	NavSystem->K2_GetRandomLocationInNavigableRadius(World, Origin, SpawnLocation, m_fSpawnRadius);
	FRotator SpawnRotation = FRotator(FRotator::ZeroRotator.Roll, UKismetMathLibrary::RandomRotator().Pitch, FRotator::ZeroRotator.Yaw);
	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, FVector(1.0f, 1.0f, 1.0f));
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParameters.Owner = this;
	AMonster* SpawnedMonster = World->SpawnActor<AMonster>(m_MonsterClass, SpawnTransform, SpawnParameters);
	SpawnedMonster->F_SetSpawner(this);
}
