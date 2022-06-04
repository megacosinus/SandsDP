// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SandsDPGameModeBase.h"
#include "SandsDPGameModeLocal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPGameModeLocal : public ASandsDPGameModeBase
{
    GENERATED_BODY()

public:
    ASandsDPGameModeLocal();

    virtual void StartPlay() override;
};
