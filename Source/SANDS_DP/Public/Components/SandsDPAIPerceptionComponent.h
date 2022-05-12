// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SandsDPAIPerceptionComponent.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPAIPerceptionComponent : public UAIPerceptionComponent
{
    GENERATED_BODY()

public:
    AActor* GetClosestEnemy() const;
};
