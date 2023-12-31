
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestLog.generated.h"

class AQuest;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTCPP1_API UQuestLog : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestLog();

protected:
	UPROPERTY()
	TArray<AQuest*> m_arQuest;
	UPROPERTY()
	AQuest* m_ActiveQuest;

public:	
	void F_AddQuestToLog(AQuest* Quest);

public:
	void F_SetActiveQuest(AQuest* Quest);

public:
	FORCEINLINE TArray<AQuest*>* F_GetarQuest() { return &m_arQuest; }
	FORCEINLINE AQuest* F_GetActiveQuest() const { return m_ActiveQuest; }
};
