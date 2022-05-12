// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SandsDPFindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPFindEnemyService : public UBTService
{
    GENERATED_BODY()

public:
    USandsDPFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
