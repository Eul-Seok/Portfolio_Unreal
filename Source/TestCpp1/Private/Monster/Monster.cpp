// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterState.h"
#include "Monster/MonsterSpawner.h"
#include "Monster/DamageIndicatorActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "ActorComponent/MonsterStatusComponent.h"
#include "ActorComponent/MonsterSkillsComponent.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widget/HeadsUpDisplay.h"
#include "Widget/TargetBar.h"
#include "Widget/TargetBarMini.h"
#include "Player/MyPlayerController.h"
#include "Player/TestCpp1Character.h"
#include "Quest/QuestLog.h"
#include "Quest/Quest.h"
#include "Item/Weapon_Base.h"


AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Scene_DamageIndicator = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_DamageIndicator"));
	Scene_DamageIndicator->SetupAttachment(RootComponent);

	Scene_StoneObject = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_StoneObject"));
	Scene_StoneObject->SetupAttachment(GetMesh(), FName("RockAttachPoint"));

	Scene_WeaponLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_WeaponLeft"));
	Scene_WeaponLeft->SetupAttachment(GetMesh(), FName("hand_l"));

	ChildActor_WeaponLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_WeaponLeft"));
	ChildActor_WeaponLeft->SetupAttachment(Scene_WeaponLeft);

	Scene_WeaponRight = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_WeaponRight"));
	Scene_WeaponRight->SetupAttachment(GetMesh(), FName("hand_r"));

	ChildActor_WeaponRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_WeaponRight"));
	ChildActor_WeaponRight->SetupAttachment(Scene_WeaponRight);

	Scene_HitBox = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_HitBox"));
	Scene_HitBox->SetupAttachment(GetMesh(), FName("pelvis"));

	HitBoxCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBoxCollision"));
	HitBoxCollision->SetupAttachment(Scene_HitBox);

	TargetIndicator = CreateDefaultSubobject<UDecalComponent>(TEXT("TargetIndicator"));
	TargetIndicator->SetupAttachment(RootComponent);
	TargetIndicator->SetVisibility(false);

	Widget_TargetBarMini = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_TargetBarMini"));
	Widget_TargetBarMini->SetupAttachment(RootComponent);
	
	MonsterStatusComponent= CreateDefaultSubobject<UMonsterStatusComponent>(TEXT("MonsterStatusComponent"));
	MonsterSkillsComponent = CreateDefaultSubobject<UMonsterSkillsComponent>(TEXT("MonsterSkillsComponent"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	m_Player = Cast<ATestCpp1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	m_LeftWeapon = Cast<AWeapon_Base>(ChildActor_WeaponLeft->GetChildActor());
	m_RightWeapon = Cast<AWeapon_Base>(ChildActor_WeaponRight->GetChildActor());
	m_LeftWeapon = Cast<AWeapon_Base>(ChildActor_WeaponLeft->GetChildActor());
	F_SetWalkSpeed(m_PatrolSpeed);
	if (GetMesh()->GetAnimInstance())
	{
		DELE_MontageEnd.BindUObject(this, &AMonster::FunctionToExecuteOnAnimationEnd);
	}
	
	m_TargetBarMini = Cast<UTargetBarMini>(Widget_TargetBarMini->GetWidget());
	m_TargetBarMini->F_SetTargetInfo(this);
	CallHiddenTargetBarMini();
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bDisplayTargetBarMini)
	{
		UpdateWidgetRotation();
	}
}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonster::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
}

void AMonster::F_CallClearTargetIndicator()
{
	TargetIndicator->SetVisibility(false);
	RemoveBinding();
}

void AMonster::RemoveBinding()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->DELE_TargetCancled.Remove(m_HandleTargetCancled);
}

void AMonster::CheckQuestMonster()
{
	TArray<AQuest*>* arQuest = m_pGameMgr->F_GetQuestLogComponent()->F_GetarQuest();
	for (uint8 i = 0; i < (* arQuest).Num(); i++)
	{
		(*arQuest)[i]->DELE_KilledTarget.Broadcast(this);
	}
}

void AMonster::MonsterDie(const FVector* pHitImactVector)
{
	CallHiddenTargetBarMini();
	AMonsterAIController* AIController = Cast<AMonsterAIController>(GetController());
	AIController->GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Key_bDeath, true);
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController->F_GetCurrentTarget() == this)
	{
		PlayerController->DELE_TargetCancled.Broadcast();
	}
	MonsterStatusComponent->F_ClearRegenTimer();

	DELE_TargetDeath.Broadcast();
	ChildActor_WeaponLeft->DestroyChildActor();
	ChildActor_WeaponRight->DestroyChildActor();
	if (m_AnimDeath)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			F_RotateToFacePlayer();
			AnimInstance->Montage_Play(m_AnimDeath, 1.0f, EMontagePlayReturnType::MontageLength);
		}
	}
	else
	{
		Ragdoll(pHitImactVector);
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Reward();
	CheckQuestMonster();
	GetWorld()->GetTimerManager().SetTimer(m_MonsterDeathTimer, this, &AMonster::MonsterSink, 5.0f, false);
}

void AMonster::MonsterSink()
{
	if (m_Spawner != nullptr)
	{
		m_Spawner->F_RemoveMonster();
	}
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetWorld()->GetTimerManager().SetTimer(m_MonsterDestroyTimer, this, &AMonster::MonsterDestroy, 2.0f, false);
}

void AMonster::MonsterDestroy()
{
	if (bBossMonster)
	{
		m_pGameMgr->DELE_GameClear.Broadcast();
	}
	Destroy();
}

void AMonster::Ragdoll(const FVector* pHitImactVector)
{
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->AddForce(*pHitImactVector * 7000, NAME_None, true);
}

AGameMgr* AMonster::F_GetGameMgr()
{
	return m_pGameMgr;
}

void AMonster::F_SetTarget()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_HandleTargetCancled = PlayerController->DELE_TargetCancled.AddUFunction(this, FName("F_CallClearTargetIndicator"));
	TargetIndicator->SetVisibility(true);
	m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_GetTargetBar()->F_SetTargetInfo(this);
}

void AMonster::F_Attack()
{
	uint8 nLength = m_arAnimDefaultAttack.Num();
	int8 nRandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, nLength-1);
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(m_arAnimDefaultAttack[nRandomIndex], 1.0f, EMontagePlayReturnType::MontageLength);
	AnimInstance->Montage_SetEndDelegate(DELE_MontageEnd, m_arAnimDefaultAttack[nRandomIndex]);
}

void AMonster::F_Hit(const UPrimitiveComponent* pOverlappedComp)
{
	float fDamage{};
	FVector ImpactPoint{};
	UParticleSystem* PlayerAttackImpact = m_Player->F_GetAttackImpact();
	m_TargetActorLocation = m_Player->GetActorLocation();
	pOverlappedComp->GetClosestPointOnCollision(HitBoxCollision->GetComponentLocation(), ImpactPoint);
	fDamage = CalculateHitDamage(pOverlappedComp);
	F_ApplyHitDamage(fDamage, &ImpactPoint);

	if (PlayerAttackImpact != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PlayerAttackImpact, ImpactPoint);
	}
	USoundBase* WeaponHitSound = Cast<AWeapon_Base>(pOverlappedComp->GetOwner())->F_GetSoundMonsterHit();
	if (WeaponHitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponHitSound, ImpactPoint);
	}
}

void AMonster::F_ApplyHitDamage(float fDamage, const FVector* pImactPointVector)
{
	AMonsterAIController* AIController = Cast<AMonsterAIController>(GetController());
	if (AIController->GetBlackboardComponent()->GetValueAsEnum(AMonsterAIController::Key_MosterState) == (uint8)EMonsterState::E_Patrol)
	{
		F_RotateToFacePlayer();
		AIController->GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::Key_Player, m_Player);
		AIController->GetBlackboardComponent()->SetValueAsEnum(AMonsterAIController::Key_MosterState, (uint8)EMonsterState::E_Chase);
	}
	FVector HitImpactVector = GetActorLocation() - *pImactPointVector;
	DisplayTargetHealthBarMini();
	RenderCustomDepthOn();
	MonsterStatusComponent->F_ReduceHealth(fDamage);
	DisplayDamageIndicator(fDamage);
	if (MonsterStatusComponent->F_GetHealthCurrent() <= 0)
	{
		RenderCustomDepthOff();
		MonsterDie(&HitImpactVector);
	}
}

void AMonster::F_RotateToFacePlayer()
{
	FVector PlayerLocation = m_Player->GetActorLocation();
	FVector MonsterLocation = GetActorLocation();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(MonsterLocation, FVector(PlayerLocation.X, PlayerLocation.Y, MonsterLocation.Z)));
}

void AMonster::F_SetWalkSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AMonster::F_SetWeaponAttackAvailable(EAttackHand AttackType, bool IsAttackAvailable)
{
	if (AttackType == EAttackHand::E_LeftHand)
	{
		m_LeftWeapon->F_SetAttackAvailable(IsAttackAvailable);
	}
	else if (AttackType == EAttackHand::E_RightHand)
	{
		m_RightWeapon->F_SetAttackAvailable(IsAttackAvailable);
	}
}

void AMonster::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	DELE_AttackEnd.Broadcast();
}

float AMonster::CalculateHitDamage(const UPrimitiveComponent* pOverlappedComp)
{
	UPlayerStatusComponent* PlayerStatusComponent = Cast<ATestCpp1Character>(pOverlappedComp->GetAttachmentRootActor())->F_GetPlayerStatusComponent();
	float PlayerStrikingPower = PlayerStatusComponent->F_GetStrikingPower();
	float PlayerBuffAppliedPower = PlayerStatusComponent->F_GetBuffAppliedStrikingPower();
	float PlayerAttackStrikingPower = PlayerStatusComponent->F_GetAttackStrikingPower();
	if (PlayerAttackStrikingPower > 0.0f)
	{
		PlayerStrikingPower = PlayerAttackStrikingPower;
	}
	else
	{
		if (PlayerBuffAppliedPower > 0.0f)
		{
			PlayerStrikingPower = PlayerBuffAppliedPower;
		}
	}
	float MonsterDefensivePower = MonsterStatusComponent->F_GetDefensivePower();
	float MonsterBuffAppliedDefensivePower = MonsterStatusComponent->F_GetBuffAppliedDefensivePower();
	if (MonsterBuffAppliedDefensivePower > 0.0f)
	{
		MonsterDefensivePower = MonsterBuffAppliedDefensivePower;
	}
	float fFinalDamage = PlayerStrikingPower - MonsterDefensivePower;
	if (fFinalDamage < 1)
	{
		fFinalDamage = 1;
	}
	return fFinalDamage;
}

void AMonster::Reward()
{
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	uint8 nLength = m_arRewardItem.Num();
	int8 nRandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, nLength - 1);
	if (m_arRewardItem.Num())
	{
		AItem* SpawnedItem = World->SpawnActor<AItem>(m_arRewardItem[nRandomIndex], GetActorTransform(), SpawnParameters);
		if (SpawnedItem)
		{
			SpawnedItem->GetStaticMeshComponent()->SetSimulatePhysics(true);
		}
	}
	m_Player->F_GetPlayerStatusComponent()->F_AddExp(m_RewardExp);
}

void AMonster::UpdateWidgetRotation()
{
	FVector WidgetLocation = Widget_TargetBarMini->GetComponentLocation();
	FVector CameraManagerLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(WidgetLocation, CameraManagerLocation);
	Widget_TargetBarMini->SetWorldRotation(NewRotation);
}

void AMonster::DisplayTargetHealthBarMini()
{
	GetWorld()->GetTimerManager().ClearTimer(m_MonsterTargetBarTimer);
	m_TargetBarMini->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_TargetBarMini->F_DisplayTargetHealthBar(true);
	bDisplayTargetBarMini = true;
	GetWorld()->GetTimerManager().SetTimer(m_MonsterTargetBarTimer, this, &AMonster::CallHiddenTargetBarMini, 10.0f, false);
}

void AMonster::CallHiddenTargetBarMini()
{
	m_TargetBarMini->SetVisibility(ESlateVisibility::Hidden);
	m_TargetBarMini->F_DisplayTargetHealthBar(false);
	bDisplayTargetBarMini = false;
}

void AMonster::RenderCustomDepthOn()
{
	GetWorld()->GetTimerManager().ClearTimer(m_MonsterRenderCustomDepthTimer);
	USkeletalMeshComponent* MonsterMesh = GetMesh();
	MonsterMesh->SetRenderCustomDepth(true);
	MonsterMesh->SetCustomDepthStencilValue(1);
	GetWorld()->GetTimerManager().SetTimer(m_MonsterRenderCustomDepthTimer, this, &AMonster::RenderCustomDepthOff, 0.2f, false);
}

void AMonster::RenderCustomDepthOff()
{
	USkeletalMeshComponent* MonsterMesh = GetMesh();
	MonsterMesh->SetRenderCustomDepth(false);
}

void AMonster::DisplayDamageIndicator(float fDamage)
{
	UWorld* world = GetWorld();
	FTransform SpawnTransform = Scene_DamageIndicator->GetComponentTransform();
	AActor* pSpawnedDamageIndicator = world->SpawnActorDeferred<ADamageIndicatorActor>(m_DamageIndicator, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (pSpawnedDamageIndicator != nullptr)
	{
		Cast<ADamageIndicatorActor>(pSpawnedDamageIndicator)->F_SetDamage(fDamage);
		pSpawnedDamageIndicator->FinishSpawning(SpawnTransform);
	}
}

void AMonster::F_SetSpawner(AMonsterSpawner* Spawner)
{
	m_Spawner = Spawner;
}

