// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DragIcon.h"
#include "Components/Image.h"

UDragIcon::UDragIcon(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), DragIcon{}, m_pDragImage{}
{
}

void UDragIcon::NativeConstruct()
{
	Super::NativeConstruct();
	DragIcon->SetBrushResourceObject(m_pDragImage);
}

void UDragIcon::F_SetDragImage(UObject* DragImage)
{
	m_pDragImage = DragImage;
}

