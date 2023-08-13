
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestLog.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTCPP1_API UQuestLog : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestLog();

protected:
	UPROPERTY()
	TArray<class AQuest*> m_arQuest;
	UPROPERTY()
	AQuest* m_ActiveQuest;

public:	
	void F_AddQuestToLog(AQuest* Quest);

public:
	void F_SetActiveQuest(AQuest* Quest);

public:
	TArray<AQuest*>* F_GetarQuest();
	AQuest* F_GetActiveQuest();
};
