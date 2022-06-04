// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SandsDPGameModeBase.h"
#include "SandsDPGameModeGlobal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPGameModeGlobal : public ASandsDPGameModeBase
{
    GENERATED_BODY()
public:
    ASandsDPGameModeGlobal();

    virtual void StartPlay() override;
};
