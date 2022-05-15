// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SandsDPCoreTypes.h"
#include "SandsDPChkDistToPlayerService.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPChkDistToPlayerService : public UBTService
{
    GENERATED_BODY()

public:
    USandsDPChkDistToPlayerService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    FBlackboardKeySelector CoolDownTimeKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    ESandsDPMatchState StateToTurnOn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float MinimumDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float CoolDownTime;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
