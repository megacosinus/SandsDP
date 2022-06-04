// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SandsDPCoreTypes.h"
#include "SandsDPGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASandsDPGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    ESandsDPMatchState GetMatchState() const { return MatchState; };
    void SetMatchState(ESandsDPMatchState State);

private:
    ESandsDPMatchState MatchState = ESandsDPMatchState::WaitingToStart;
};
