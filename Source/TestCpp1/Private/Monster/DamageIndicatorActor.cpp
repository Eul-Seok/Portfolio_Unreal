
#include "Monster/DamageIndicatorActor.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/DamageIndicator.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


ADamageIndicatorActor::ADamageIndicatorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Scene_Default = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_WeaponRight"));
	RootComponent = Scene_Default;
	Widget_DamageIndicator = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_DamageIndicator"));
	Widget_DamageIndicator->SetupAttachment(RootComponent);
}

void ADamageIndicatorActor::BeginPlay()
{
	Super::BeginPlay();
	UDamageIndicator* W_DamageIndicator = Cast<UDamageIndicator>(Widget_DamageIndicator->GetWidget());
	W_DamageIndicator->F_SetDamage(m_fDamage);
	m_vStartLocation = GetActorLocation();
	m_vEndLocation = m_vStartLocation + FVector(-40.0f, -40.0f, 80.0f);
	if (CurveFloat_Move)
	{
		FOnTimelineFloat TimelineProgressCallback;
		FOnTimelineEvent TimelineFinishedCallback;
		TimelineProgressCallback.BindUFunction(this, FName("Move"));
		TimelineFinishedCallback.BindUFunction(this, FName("ActorDestroy"));
		Timeline_Move.AddInterpFloat(CurveFloat_Move, TimelineProgressCallback);
		Timeline_Move.SetTimelineFinishedFunc(TimelineFinishedCallback);
		Timeline_Move.SetTimelineLength(0.7f);
	}
	Timeline_Move.PlayFromStart();
}

void ADamageIndicatorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline_Move.TickTimeline(DeltaTime);

}

void ADamageIndicatorActor::Move()
{
	float TimelineValue = CurveFloat_Move->GetFloatValue(Timeline_Move.GetPlaybackPosition());
	FVector NewLocation = UKismetMathLibrary::VLerp(m_vStartLocation, m_vEndLocation, CurveFloat_Move->GetFloatValue(TimelineValue));
	SetActorRelativeLocation(NewLocation);
}

void ADamageIndicatorActor::ActorDestroy()
{
	Destroy();
}

void ADamageIndicatorActor::F_SetDamage(float fDamage)
{
	m_fDamage = fDamage;
}


