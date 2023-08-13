// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Item/ItemType.h"
#include "Affect/AffectType.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType m_ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AItem> m_ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffectType m_eAffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fAffectValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_ItemDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)  
	UStaticMesh* m_StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* m_ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_ItemCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsEnable;
};
