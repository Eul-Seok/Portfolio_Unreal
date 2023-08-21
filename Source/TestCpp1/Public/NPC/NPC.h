
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

class AQuest;

UCLASS()
class TESTCPP1_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Scene_InteractBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* InteractBoxCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Scene_TextRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* TextRenderHasQuest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* TextRenderNPCName;


protected:
	class AGameMgr* m_pGameMgr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> m_arQuestActor;
	bool m_bHasQuest;
	uint8 m_nCurrentQuestIndex;
	FRotator m_RotationDefault;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	bool CheckPreRequisiteQuest(AQuest* Quest);
	bool CanDisplayQuest();
	bool CheckAcceptQuest();
	void UpdateTextRenderRotation(UTextRenderComponent* TextRender);

public:
	void F_DisplayQuestContent();
	void F_InteractionNPC();
	void F_QuestComplete();
	void F_RotateToFacePlayer(AActor* Player);
	void F_RotationReset();

public:	
	bool F_CheckHasQuest();
	void F_DisplayTextRenderHasQuest(bool bDisplay);
	UFUNCTION()
	void F_CallUpdateTextRenderHasQuest();

public:
	FDele_Multi DELE_UpdateTextRenderHasQuest;
};
