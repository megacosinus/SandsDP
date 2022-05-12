#pragma once
#include "SandsDPCoreTypes.generated.h"

/** Used to show game state */
UENUM(BlueprintType)
enum class ESandsDPMatchState : uint8
{
    WaitingToStart = 0,
    InRealtimeGame,
    InTacticalPause,
    InMenuPause,
    GameOver
};

/** Delegate about changed game state */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESandsDPMatchState);