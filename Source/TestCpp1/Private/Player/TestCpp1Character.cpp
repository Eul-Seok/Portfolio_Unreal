#include "Player/TestCpp1Character.h"
#include "Player/MyPlayerController.h"
#include "Monster/Monster.h"
#include "NPC/NPC.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "Components/ChildActorComponent.h"
#include "ActorComponent/PlayerStatusComponent.h"
#include "ActorComponent/MonsterStatusComponent.h"
#include "ActorComponent/PlayerSkillsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/GameMgr.h"
#include "Manager/WidgetManager.h"
#include "Widget/HeadsUpDisplay.h"
#include "Item/Item.h"
#include "Item/Weapon_Base.h"
#include "Engine/TargetPoint.h"

ATestCpp1Character::ATestCpp1Character() :
	CameraBoom{}, FollowCamera{}, m_pGameMgr{}, m_PlayerController{}, m_setOverlapItem{}
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Scene_UnequipSword = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_UnequipSword"));
	Scene_UnequipSword->SetupAttachment(GetMesh(), FName("Socket-UnequipSword"));

	Scene_UnequipBow = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_UnequipBow"));
	Scene_UnequipBow->SetupAttachment(GetMesh());

	Scene_WeaponRight = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_WeaponRight"));
	Scene_WeaponRight->SetupAttachment(GetMesh(), FName("Socket-WeaponRight"));
	ChildActor_WeaponRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_WeaponRight"));
	ChildActor_WeaponRight->SetupAttachment(Scene_WeaponRight);

	Scene_WeaponLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_WeaponLeft"));
	Scene_WeaponLeft->SetupAttachment(GetMesh(), FName("Socket-WeaponLeft"));
	Scene_HitBox = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_HitBox"));
	Scene_HitBox->SetupAttachment(GetMesh(), FName("pelvis")); 

	HitBoxCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBoxCollision"));
	HitBoxCollision->SetupAttachment(Scene_HitBox);

	PickUpBoxCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpBoxCollision"));
	PickUpBoxCollision->SetupAttachment(RootComponent);
	
	TargetingBoxCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TargetingBoxCollision"));
	TargetingBoxCollision->SetupAttachment(RootComponent);
	
	InteractBoxCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractBoxCollision"));
	InteractBoxCollision->SetupAttachment(RootComponent);

	PlayerStatusComponent = CreateDefaultSubobject<UPlayerStatusComponent>(TEXT("PlayerStatusComponent"));
	PlayerSkillsComponent = CreateDefaultSubobject<UPlayerSkillsComponent>(TEXT("PlayerSkillsComponent"));
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBLUEPRINT_KATANA(TEXT("/Game/Player/Animation/BP_Anim_Katana"));
	if (ANIMBLUEPRINT_KATANA.Succeeded())
	{
		m_AnimBlueprintKatana = ANIMBLUEPRINT_KATANA.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find BP_Anim_Katana"));
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBLUEPRINT_HAND(TEXT("/Game/Player/Animation/BP_Anim_Hand"));
	if (ANIMBLUEPRINT_HAND.Succeeded())
	{
		m_AnimBlueprintHand = ANIMBLUEPRINT_HAND.Class;
		UE_LOG(LogTemp, Warning, TEXT("Find BP_Anim_Hand"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEFATULKATANAATTACK_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_DefaultAttack_Montage"));
	if (DEFATULKATANAATTACK_MONTAGE.Succeeded())
	{
		m_AnimKatanaDefaultAttack = DEFATULKATANAATTACK_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_DefaultAttack_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEFATULHANDATTACK_MONTAGE(TEXT("/Game/Player/Animation/Hand/Hand_DefaultAttack_Montage"));
	if (DEFATULHANDATTACK_MONTAGE.Succeeded())
	{
		m_AnimHandDefaultAttack = DEFATULHANDATTACK_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Hand_DefaultAttack_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ONEHANDWEAPONEQUIPPED_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_OneHandWeaponEquipped_Montage"));
	if (ONEHANDWEAPONEQUIPPED_MONTAGE.Succeeded())
	{
		m_AnimOneHandWeaponEquipped = ONEHANDWEAPONEQUIPPED_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_OneHandWeaponEquipped_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ONEHANDWEAPONUNEQUIPPED_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_OneHandWeaponUnequipped_Montage"));
	if (ONEHANDWEAPONUNEQUIPPED_MONTAGE.Succeeded())
	{
		m_AnimOneHandWeaponUnequipped = ONEHANDWEAPONUNEQUIPPED_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_OneHandWeaponUnequipped_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PLAYERDIE_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_PlayerDie_Montage"));
	if (PLAYERDIE_MONTAGE.Succeeded())
	{
		m_AnimPlayerDie = PLAYERDIE_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_PlayerDie_Montage"));
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> EVASION_F_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_Evasion_F_Montage"));
	if (EVASION_F_MONTAGE.Succeeded())
	{
		m_AnimEvasion_F = EVASION_F_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_Evasion_F_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EVASION_B_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_Evasion_B_Montage"));
	if (EVASION_B_MONTAGE.Succeeded())
	{
		m_AnimEvasion_B = EVASION_B_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_Evasion_B_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EVASION_R_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_Evasion_R_Montage"));
	if (EVASION_R_MONTAGE.Succeeded())
	{
		m_AnimEvasion_R = EVASION_R_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_Evasion_R_Montage"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EVASION_L_MONTAGE(TEXT("/Game/Player/Animation/Katana/Katana_Evasion_L_Montage"));
	if (EVASION_L_MONTAGE.Succeeded())
	{
		m_AnimEvasion_L = EVASION_L_MONTAGE.Object;
		UE_LOG(LogTemp, Warning, TEXT("Find Katana_Evasion_L_Montage"));
	}
}

void ATestCpp1Character::BeginPlay()
{
	Super::BeginPlay();
	m_PlayerController = Cast<AMyPlayerController>(GetController());
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;
	
	BindOverapEvent();
	if (GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ATestCpp1Character::PlayMontageNotifyBegin);
		CompleteDelegate.BindUObject(this, &ATestCpp1Character::FunctionToExecuteOnAnimationEnd);
		CompleteDelegateEquip.BindUObject(this, &ATestCpp1Character::FunctionToExecuteOnAnimationEndEquip);
	}

	m_RightHandWeapon = Cast<AWeapon_Base>(ChildActor_WeaponRight->GetChildActor());
	m_CurrentSkillWeaponType = ESkillWeaponType::E_Default;
}

void ATestCpp1Character::PlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	m_nAttackCombo--;
	if (m_nAttackCombo < 0)
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.20f, m_AnimKatanaDefaultAttack);
		m_nAttackCombo = 0;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void ATestCpp1Character::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	ResetAnimationCondition();
}

void ATestCpp1Character::FunctionToExecuteOnAnimationEndEquip(UAnimMontage* animMontage, bool bInterrupted)
{
	m_bPlayingMontage = false;
	if (bInterrupted)
	{
		GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ATestCpp1Character::ResetAnimInstance, 0.1f, false);
	}
}

void ATestCpp1Character::BindOverapEvent()
{
	PickUpBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATestCpp1Character::OnOverlapBegin);
	PickUpBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATestCpp1Character::OnOverlapEnd);
	TargetingBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATestCpp1Character::OnOverlapBeginMonster);
	TargetingBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATestCpp1Character::OnOverlapEndMonster);
	InteractBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATestCpp1Character::OnOverlapBeginNPC);
	InteractBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATestCpp1Character::OnOverlapEndNPC);
}

float ATestCpp1Character::CalculateHitDamage(UPrimitiveComponent* OverlappedComp)
{
	UMonsterStatusComponent* MonsterStatusComponent = Cast<AMonster>(OverlappedComp->GetAttachmentRootActor())->F_GetMonsterStatusComponent();
	float MonsterStrikingPower = MonsterStatusComponent->F_GetStrikingPower();
	float MonsterBuffAppliedStrikingPower = MonsterStatusComponent->F_GetBuffAppliedStrikingPower();
	float MonsterAttackStrikingPower = MonsterStatusComponent->F_GetAttackStrikingPower();
	if (MonsterAttackStrikingPower > 0.0f)
	{
		MonsterStrikingPower = MonsterAttackStrikingPower;
	}
	else
	{
		if (MonsterBuffAppliedStrikingPower > 0.0f)
		{
			MonsterStrikingPower = MonsterBuffAppliedStrikingPower;
		}
	}
	float PlayerDefensivePower = PlayerStatusComponent->F_GetDefensivePower();
	float PlayerBuffAppliedDefensivePower = PlayerStatusComponent->F_GetBuffAppliedDefensivePower();
	if (PlayerBuffAppliedDefensivePower > 0.0f)
	{
		PlayerDefensivePower = PlayerBuffAppliedDefensivePower;
	}
	float fFinalDamage = MonsterStrikingPower - PlayerDefensivePower;
	if (fFinalDamage < 1)
	{
		fFinalDamage = 1;
	}
	return fFinalDamage;
}

void ATestCpp1Character::PlayerDie()
{
	m_PlayerController->F_InputModePlayerDeath();
	m_bDeath = true;
	PlayerStatusComponent->F_ClearRegenTimer();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (m_AnimPlayerDie)
	{
		AnimInstance->Montage_Play(m_AnimPlayerDie, 1.0f, EMontagePlayReturnType::MontageLength);
	}
	HitBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DELE_PlayerDeath.Broadcast();
	Tags.Remove(FName("Player"));

	m_pGameMgr->F_GetWidgetMgr()->F_ToggleRevivalMenu();
}

void ATestCpp1Character::StopStun()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Stop(0.2f, m_AnimStun);
	m_PlayerController->F_InputModePlayerStun(false);
	m_bPlayingMontage = false;
}

void ATestCpp1Character::ResetAnimationCondition()
{
	m_nAttackCombo = 0;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	if (m_bEvasion)
	{
		m_bEvasion = false;
		HitBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	if (!GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.IsBound())
	{
		GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ATestCpp1Character::PlayMontageNotifyBegin);
	}
}

void ATestCpp1Character::ChangeAnimInstance()
{
	if (!m_bOneHandWeaponEquippeed)
	{
		GetMesh()->SetAnimInstanceClass(m_AnimBlueprintKatana);
		m_RightHandWeapon = m_Weapon;
		m_CurrentSkillWeaponType = ESkillWeaponType::E_Katana;
	}
	else
	{
		GetMesh()->SetAnimInstanceClass(m_AnimBlueprintHand);
		m_RightHandWeapon = Cast<AWeapon_Base>(ChildActor_WeaponRight->GetChildActor());
		m_CurrentSkillWeaponType = ESkillWeaponType::E_Default;
	}
	ResetAnimationCondition();
}

void ATestCpp1Character::ResetAnimInstance()
{
	if (!m_bDeath)
	{
		if (m_bOneHandWeaponEquippeed)
		{
			GetMesh()->SetAnimInstanceClass(m_AnimBlueprintKatana);
			m_RightHandWeapon = m_Weapon;
			m_CurrentSkillWeaponType = ESkillWeaponType::E_Katana;
		}
		else
		{
			GetMesh()->SetAnimInstanceClass(m_AnimBlueprintHand);
			m_RightHandWeapon = Cast<AWeapon_Base>(ChildActor_WeaponRight->GetChildActor());
			m_CurrentSkillWeaponType = ESkillWeaponType::E_Default;
		}
		ResetAnimationCondition();
	}
}

void ATestCpp1Character::RenderCustomDepthOn()
{
	GetWorld()->GetTimerManager().ClearTimer(m_PlayerRenderCustomDepthTimer);
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	PlayerMesh->SetRenderCustomDepth(true);
	GetWorld()->GetTimerManager().SetTimer(m_PlayerRenderCustomDepthTimer, this, &ATestCpp1Character::RenderCustomDepthOff, 0.2f, false);
}


void ATestCpp1Character::RenderCustomDepthOff()
{
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	PlayerMesh->SetRenderCustomDepth(false);
}

void ATestCpp1Character::F_TargetingModeOn()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ATestCpp1Character::F_TargetingModeOff()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATestCpp1Character::F_CreateWeapon(TSubclassOf<AWeapon_Base> Weapon)
{
	UWorld* world = GetWorld();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	m_Weapon = world->SpawnActor<AWeapon_Base>(Weapon, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	m_Weapon->AttachToComponent(Scene_UnequipSword, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_Weapon->F_DestroyPickUpRange();
	m_bHasWeapon = true;
}

void ATestCpp1Character::F_OneHandWeaponEquipped()
{
	bool bjump = (EMovementMode::MOVE_Falling == GetCharacterMovement()->MovementMode);
	
	if (m_bHasWeapon && !m_bPlayingMontage && !bjump)
	{
		ChangeAnimInstance();
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (m_bOneHandWeaponEquippeed)
		{
			AnimInstance->Montage_Play(m_AnimOneHandWeaponUnequipped, 1.0f, EMontagePlayReturnType::MontageLength);
			AnimInstance->Montage_SetEndDelegate(CompleteDelegateEquip, m_AnimOneHandWeaponUnequipped);
			m_bPlayingMontage = true;
		}
		else
		{
			AnimInstance->Montage_Play(m_AnimOneHandWeaponEquipped, 1.0f, EMontagePlayReturnType::MontageLength);
			AnimInstance->Montage_SetEndDelegate(CompleteDelegateEquip, m_AnimOneHandWeaponEquipped);
			m_bPlayingMontage = true;
		}
	}
	else if (!m_bHasWeapon)
	{
		FText AlertText = FText::FromString(FString::Printf(TEXT("먼저, 인벤토리에서 카타나를 장착해주세요")));
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayTextAlert(&AlertText);
	}
}

void ATestCpp1Character::F_SetWeaponAttackAvailable(bool IsAttackAvailable)
{
	m_RightHandWeapon->F_SetAttackAvailable(IsAttackAvailable);
}

void ATestCpp1Character::F_DefaultAttack()
{
	UAnimMontage* DefaultAttack = m_AnimHandDefaultAttack;
	if (m_bOneHandWeaponEquippeed)
	{
		DefaultAttack = m_AnimKatanaDefaultAttack;
	}
	bool bMontagePlaying = GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();
	if (bMontagePlaying)
	{
		m_nAttackCombo = 1;
	}
	else
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		
		AnimInstance->Montage_Play(DefaultAttack, 1.0f, EMontagePlayReturnType::MontageLength);
		AnimInstance->Montage_SetEndDelegate(CompleteDelegate, DefaultAttack);
	}
}

bool ATestCpp1Character::F_CheckMana(float ManaCost)
{
	bool bSuccess{};
	float CurrentMana = PlayerStatusComponent->F_GetManaCurrent();
	bSuccess = CurrentMana >= ManaCost;
	return bSuccess;
}

void ATestCpp1Character::F_Hit(UPrimitiveComponent* OverlappedComp)
{
	if (!m_bDeath)
	{
		RenderCustomDepthOn();
		float fDamage{};
		FVector ImpactPoint{};
		UParticleSystem* MonsterAttackImpact = Cast<AMonster>(OverlappedComp->GetAttachmentRootActor())->F_GetAttackImpact();
		m_TargetActorLocation = OverlappedComp->GetAttachmentRootActor()->GetActorLocation();
		OverlappedComp->GetClosestPointOnCollision(HitBoxCollision->GetComponentLocation(), ImpactPoint);
		fDamage = CalculateHitDamage(OverlappedComp);
		F_ApplyHitDamage(fDamage, &ImpactPoint);
		
		if (MonsterAttackImpact != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MonsterAttackImpact, ImpactPoint);
		}
		if(m_SoundHit)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_SoundHit, ImpactPoint);
	}
}

void ATestCpp1Character::F_ApplyHitDamage(float fDamage, FVector* vHitImactPoint)
{
	FVector HitImpactVector = GetActorLocation() - *vHitImactPoint;
	PlayerStatusComponent->F_ReduceHealth(fDamage);
	if (PlayerStatusComponent->F_GetHealthCurrent() <= 0)
	{
		RenderCustomDepthOff();
		PlayerDie();
	}
}

void ATestCpp1Character::F_PlayKnockBack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(m_TargetActorLocation.X, m_TargetActorLocation.Y, GetActorLocation().Z)));
	AnimInstance->Montage_Play(m_AnimKnockBack, 1.0f, EMontagePlayReturnType::MontageLength);
	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundKnockBack);
}

void ATestCpp1Character::F_PlayStun(float fDuration)
{
	GetWorld()->GetTimerManager().ClearTimer(m_PlayerStunTimer);
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(m_TargetActorLocation.X, m_TargetActorLocation.Y, GetActorLocation().Z)));
	AnimInstance->Montage_Play(m_AnimStun, 1.0f, EMontagePlayReturnType::MontageLength);
	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundKnockBack);
	m_PlayerController->F_InputModePlayerStun(true);
	m_bPlayingMontage = true;
	GetWorld()->GetTimerManager().SetTimer(m_PlayerStunTimer, this, &ATestCpp1Character::StopStun, fDuration, false);
}

void ATestCpp1Character::F_Evasion(float Direction)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	bool bjump = (EMovementMode::MOVE_Falling == GetCharacterMovement()->MovementMode);
	if (!bjump && !m_bEvasion)
	{
		m_bEvasion = true;
		HitBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (Direction < 45.0f && Direction > -45.0f)
		{
			AnimInstance->Montage_Play(m_AnimEvasion_F, 0.8f, EMontagePlayReturnType::MontageLength);
			AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimEvasion_F);
		}
		else if (Direction >= 45.0f && Direction < 135.0f)
		{
			AnimInstance->Montage_Play(m_AnimEvasion_R, 0.8f, EMontagePlayReturnType::MontageLength);
			AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimEvasion_R);
		}
		else if (Direction <= -45.0f && Direction > -135.0f)
		{
			AnimInstance->Montage_Play(m_AnimEvasion_L, 0.8f, EMontagePlayReturnType::MontageLength);
			AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimEvasion_L);
		}
		else
		{
			AnimInstance->Montage_Play(m_AnimEvasion_B, 0.8f, EMontagePlayReturnType::MontageLength);
			AnimInstance->Montage_SetEndDelegate(CompleteDelegate, m_AnimEvasion_B);
		}
	}
}

void ATestCpp1Character::F_Revival()
{
	m_PlayerController->F_InputModePlayerRevival();
	m_bDeath = false;
	PlayerStatusComponent->F_SetRegenTimer();
	PlayerStatusComponent->F_CompleteRecovery();
	PlayerStatusComponent->DELE_RequestUpdateStatusBar.Broadcast();
	SetActorTransform(m_RevivalPoint->GetActorTransform());
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Stop(0.20f, m_AnimPlayerDie);
	HitBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Tags.Add(FName("Player")); 
	m_pGameMgr->F_GetWidgetMgr()->F_ToggleRevivalMenu();
}

void ATestCpp1Character::F_OverlapItemAdd(AItem* Item)
{
	m_setOverlapItem.Add(Item);
	m_nOverlapItemCount++;
}

void ATestCpp1Character::F_OverlapItemRemove(AItem* Item)
{
	m_setOverlapItem.Remove(Item);
	m_setOverlapItem.CompactStable();
	m_setOverlapItem.Shrink();
	m_nOverlapItemCount--;
}

void ATestCpp1Character::F_OverlapMonsterAdd(AMonster* Monster)
{
	m_setOverlapMonster.Add(Monster);
}

void ATestCpp1Character::F_OverlapMonsterRemove(AMonster* Monster)
{
	m_setOverlapMonster.Remove(Monster);
}

void ATestCpp1Character::F_SetbOneHandWeaponEquippeed(bool IsEquipped)
{
	m_bOneHandWeaponEquippeed = IsEquipped;
}

void ATestCpp1Character::F_SetbCasting(bool IsCasting)
{
	m_bCasting = IsCasting;
}

void ATestCpp1Character::F_SetbPlayingMontage(bool IsPlayingMontage)
{
	m_bPlayingMontage = IsPlayingMontage;
}

UPlayerStatusComponent* ATestCpp1Character::F_GetPlayerStatusComponent()
{
	return PlayerStatusComponent;
}

UPlayerSkillsComponent* ATestCpp1Character::F_GetPlayerSkillsComponent()
{
	return PlayerSkillsComponent;
}

USceneComponent* ATestCpp1Character::F_GetSceneWeaponRigth()
{
	return Scene_WeaponRight;
}

USceneComponent* ATestCpp1Character::F_GetSceneUnequipSword()
{
	return Scene_UnequipSword;
}

TSet<AItem*>* ATestCpp1Character::F_GetOverLapItem()
{
	return &m_setOverlapItem;
}

TSet<AMonster*>* ATestCpp1Character::F_GetOverLapMonster()
{
	return &m_setOverlapMonster;
}

AWeapon_Base* ATestCpp1Character::F_GetRightHandWeapon()
{
	return m_RightHandWeapon;
}

AWeapon_Base* ATestCpp1Character::F_GetWeapon()
{
	return m_Weapon;
}


AGameMgr* ATestCpp1Character::F_GetGameMgr()
{
	return m_pGameMgr;
}

bool ATestCpp1Character::F_GetbCasting()
{
	return m_bCasting;
}

bool ATestCpp1Character::F_GetbPlayingMontage()
{
	return m_bPlayingMontage;
}

UParticleSystem* ATestCpp1Character::F_GetAttackImpact()
{
	return m_AttackImpact;
}

ANPC* ATestCpp1Character::F_GetOverlapNPC()
{
	return m_pOverlapNPC;
}

ESkillWeaponType ATestCpp1Character::F_GetCurrentSkillWeaponType()
{
	return m_CurrentSkillWeaponType;
}

void ATestCpp1Character::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AItem* Item = Cast<AItem>(OtherActor))
	{
		if (m_nOverlapItemCount == 0)
		{
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayInteractionAlert(true, EInteractionAlertType::E_InteractPickup);
		}
		F_OverlapItemAdd(Item);
		m_setOverlapItem.Array()[0]->GetStaticMeshComponent()->SetRenderCustomDepth(true);
	}
}

void ATestCpp1Character::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AItem* Item = Cast<AItem>(OtherActor))
	{
		Item->GetStaticMeshComponent()->SetRenderCustomDepth(false);
		F_OverlapItemRemove(Item);
		if (m_nOverlapItemCount == 0)
			m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayInteractionAlert(false, EInteractionAlertType::E_InteractPickup);
		else
		{
			if (m_setOverlapItem.Array().IsValidIndex(0))
			{
				m_setOverlapItem.Array()[0]->GetStaticMeshComponent()->SetRenderCustomDepth(true);
			}
		}	
	}
}

void ATestCpp1Character::OnOverlapBeginNPC(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ANPC* NPC = Cast<ANPC>(OtherActor))
	{
		NPC->GetMesh()->SetRenderCustomDepth(true);
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayInteractionAlert(true, EInteractionAlertType::E_Interact);
		m_pOverlapNPC = NPC;
	}
}

void ATestCpp1Character::OnOverlapEndNPC(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ANPC* NPC = Cast<ANPC>(OtherActor))
	{
		NPC->GetMesh()->SetRenderCustomDepth(false);
		m_pGameMgr->F_GetWidgetMgr()->F_GetHUD()->F_DisplayInteractionAlert(false, EInteractionAlertType::E_Interact);
		m_pOverlapNPC = nullptr;
		NPC->F_RotationReset();
	}
}

void ATestCpp1Character::OnOverlapBeginMonster(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMonster* Monster = Cast<AMonster>(OtherActor))
	{
		F_OverlapMonsterAdd(Monster);
	}
}

void ATestCpp1Character::OnOverlapEndMonster(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMonster* Monster = Cast<AMonster>(OtherActor))
	{
		F_OverlapMonsterRemove(Monster);
		if (m_PlayerController->F_GetCurrentTarget() == Monster)
		{
			m_PlayerController->DELE_TargetCancled.Broadcast();
		}
	}
}

