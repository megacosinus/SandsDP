// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/SandsDPBaseCharacter.h"
#include "SandsDPAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SANDS_DP_API ASandsDPAICharacter : public ASandsDPBaseCharacter
{
    GENERATED_BODY()

public:
    ASandsDPAICharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
    UBehaviorTree* BehaviorTreeAsset;
};
