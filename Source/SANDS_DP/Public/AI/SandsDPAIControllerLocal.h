// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AI/SandsDPAIController.h"
#include "SandsDPAIControllerLocal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPAIControllerLocal : public ASandsDPAIController
{
    GENERATED_BODY()

protected:
    virtual void OnPossess(APawn* InPawn) override;
};
