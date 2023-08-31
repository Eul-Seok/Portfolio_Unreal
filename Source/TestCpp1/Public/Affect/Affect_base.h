// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/Interface_Affect.h"
#include "Affect_base.generated.h"

UCLASS()
class TESTCPP1_API UAffect_base : public UObject, public IInterface_Affect
{
	GENERATED_BODY()
	
public:
	UAffect_base();

protected:
	class IInterface_StatusComponent* m_Interface_StatusComponent;
	FText m_AlertText;

public:
	virtual bool F_Apply(ACharacter* Character, float fValue, EOperatorType eOperator) override;
	virtual void F_ResetApply(ACharacter* Character) override;
};
