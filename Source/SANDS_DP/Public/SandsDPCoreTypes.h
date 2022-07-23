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
    InMenuBeforeBattlePause,
    InBattle,
    GameOver
};

/** Delegate about changed game state */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESandsDPMatchState);

/** Health */
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);