// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Item.h"
#include "UObject/ConstructorHelpers.h"
#include "Manager/GameMgr.h"
#include "Manager/InventoryManager.h"
#include "Player/TestCpp1Character.h"
#include "Components/PrimitiveComponent.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include <Engine/Classes/Components/SphereComponent.h>

AItem::AItem() :
	ItemMesh{}, PickUpRange {}, m_pItemDataTable{}, m_pGameMgr{}, m_RowName{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_pGameMgr = GetWorld() != nullptr ? GetWorld()->GetGameState<AGameMgr>() : nullptr;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PickUpRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpRange"));
	RootComponent = ItemMesh;
	PickUpRange->SetupAttachment(RootComponent);
	m_RowName = FName("Default");
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

bool AItem::F_ItemGet(ATestCpp1Character* Character)
{
	bool bSuccess{};
	if (Character)
	{
		bSuccess = Character->F_GetGameMgr()->F_GetInventoryMgr()->F_ItemAdd(&m_RowName);
		if(bSuccess)
		{
			Destroy();
			return bSuccess;
		}
		return bSuccess;
	}
	else
	{
		return bSuccess;
	}
}

void AItem::F_DestroyPickUpRange()
{
	PickUpRange->DestroyComponent();
}


