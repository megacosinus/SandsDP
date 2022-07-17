// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/SandsDPPlayerController.h"
#include "SandsDPPlayerControllerLocal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPPlayerControllerLocal : public ASandsDPPlayerController
{
    GENERATED_BODY()

public:
    ASandsDPPlayerControllerLocal();

private:
    // Implement The Generic Team Interface
    FGenericTeamId TeamId;
    FGenericTeamId GetGenericTeamId() const;
};
