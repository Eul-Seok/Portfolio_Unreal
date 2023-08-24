// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest/QuestObjectiveData.h"
#include "Quest.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Multi_OneParam, AActor*);

class AItem;

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
	TArray<TSubclassOf<AItem>> m_arRewardItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_RewardExp;
	uint8 m_nCurrentAchievementCount;
	bool m_bComplete;
	bool m_bAccept;

protected:
	virtual void BeginPlay() override;

protected:
	void CheckObjective(EQuestType QuestType, const AActor* Target);
	UFUNCTION()
	void CallCheckLocationObjective(const AActor* LocationReached);
	UFUNCTION()
	void CallCheckInteractionObjective(const AActor* InteractionTarget);
	UFUNCTION()
	void CallCheckCollectionObjective(const AActor* CollectedItem);
	UFUNCTION()
	void CallCheckKilledTargetObjective(const AActor* KilledTarget);

public:
	void F_Reward();

public:
	void F_SetbComplete(bool IsComplete);
	void F_SetbAccept(bool IsAccept);

public:	
	FORCEINLINE FText* F_GetName() { return &m_Name; }
	FORCEINLINE FText* F_GetDescription() { return &m_Description; }
	FORCEINLINE TArray<FQuestObjectiveData>* F_GetObjectiveData() { return &m_arObjectiveData; }
	FORCEINLINE bool F_GetbStoryQuest() { return m_bStoryQuest; }
	FORCEINLINE bool F_GetbComplete() { return m_bComplete; }
	FORCEINLINE bool F_GetbAccept() { return m_bAccept; }
	FORCEINLINE uint8 F_GetCurrentAchievementCount() { return m_nCurrentAchievementCount; }
	FORCEINLINE AQuest* F_GetPreRequisiteQuest() { return m_PreRequisiteQuest; }
	FORCEINLINE TArray<TSubclassOf<AItem>>* F_GetarRewardItem() { return &m_arRewardItem; }
	FORCEINLINE float F_GetRewardExp() { return m_RewardExp; }

public:
	FDele_Multi_OneParam DELE_LocationReached;
	FDele_Multi_OneParam DELE_InteractionTarget;
	FDele_Multi_OneParam DELE_CollectedItem;
	FDele_Multi_OneParam DELE_KilledTarget;
};
