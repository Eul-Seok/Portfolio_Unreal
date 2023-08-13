
#pragma once

#include "CoreMinimal.h"
#include "QuickSlotNumber.generated.h"

class TESTCPP1_API QuickSlotNumber
{
public:
	QuickSlotNumber();
	~QuickSlotNumber();
};

UENUM(BlueprintType)
enum class EQuickSlotNumber : uint8
{
	E_Default		UMETA(DisplayName = Default),
	E_QuickSlot1	UMETA(DisplayName = QuickSlot1),
	E_QuickSlot2	UMETA(DisplayName = QuickSlot2),
	E_QuickSlot3	UMETA(DisplayName = QuickSlot3),
	E_QuickSlot4	UMETA(DisplayName = QuickSlot4),
	E_QuickSlot5	UMETA(DisplayName = QuickSlot5),
	E_QuickSlot6	UMETA(DisplayName = QuickSlot6),
	E_QuickSlot7	UMETA(DisplayName = QuickSlot7),
	E_QuickSlot8	UMETA(DisplayName = QuickSlot8),
	E_QuickSlot9	UMETA(DisplayName = QuickSlot9),
	E_QuickSlot10	UMETA(DisplayName = QuickSlot10),
	E_QuickSlot11	UMETA(DisplayName = QuickSlot11),
	E_QuickSlot12	UMETA(DisplayName = QuickSlot12),
	E_QuickSlot13	UMETA(DisplayName = QuickSlot13),
	E_QuickSlot14	UMETA(DisplayName = QuickSlot14),
	E_Max			UMETA(DisplayName = Max)
};

