// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SandsDPFireService.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPFireService : public UBTService
{
    GENERATED_BODY()

public:
    USandsDPFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
