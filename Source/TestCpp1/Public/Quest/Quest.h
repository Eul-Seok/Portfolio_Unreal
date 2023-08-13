// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest/QuestObjectiveData.h"
#include "Quest.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Multi_OneParam, AActor*);

UCLASS()
class TESTCPP1_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuest();

protected:
	UFUNCTION(CallInEditor)
	void OrganiseQuestInEditor();

protected:
	class AGameMgr* m_pGameMgr;
	class ATestCpp1Character* m_Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ANPC* m_QuestOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestObjectiveData> m_arObjectiveData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_bStoryQuest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AQuest* m_PreRequisiteQuest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AItem>> m_arRewardItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_RewardExp;
	uint8 m_nCurrentAchievementCount;
	bool m_bComplete;
	bool m_bAccept;

protected:
	virtual void BeginPlay() override;

protected:
	void CheckObjective(EQuestType QuestType, AActor* Target);
	UFUNCTION()
	void CallCheckLocationObjective(AActor* LocationReached);
	UFUNCTION()
	void CallCheckInteractionObjective(AActor* InteractionTarget);
	UFUNCTION()
	void CallCheckCollectionObjective(AActor* CollectedItem);
	UFUNCTION()
	void CallCheckKilledTargetObjective(AActor* KilledTarget);

public:
	void F_Reward();

public:
	void F_SetbComplete(bool IsComplete);
	void F_SetbAccept(bool IsAccept);
public:	
	FText* F_GetName();
	FText* F_GetDescription();
	TArray<FQuestObjectiveData>* F_GetObjectiveData();
	bool F_GetbStoryQuest();
	bool F_GetbComplete();
	bool F_GetbAccept();
	uint8 F_GetCurrentAchievementCount();
	AQuest* F_GetPreRequisiteQuest();
	TArray<TSubclassOf<class AItem>>* F_GetarRewardItem();
	float F_GetRewardExp();

public:
	FDele_Multi_OneParam DELE_LocationReached;
	FDele_Multi_OneParam DELE_InteractionTarget;
	FDele_Multi_OneParam DELE_CollectedItem;
	FDele_Multi_OneParam DELE_KilledTarget;
};
