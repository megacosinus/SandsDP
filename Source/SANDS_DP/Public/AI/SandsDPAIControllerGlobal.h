// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AI/SandsDPAIController.h"
#include "SandsDPAIControllerGlobal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPAIControllerGlobal : public ASandsDPAIController
{
    GENERATED_BODY()

protected:
    virtual void OnPossess(APawn* InPawn) override;
};
