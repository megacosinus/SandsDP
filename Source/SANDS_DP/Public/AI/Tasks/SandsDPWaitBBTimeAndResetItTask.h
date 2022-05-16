// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_WaitBlackboardTime.h"
#include "SandsDPWaitBBTimeAndResetItTask.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPWaitBBTimeAndResetItTask : public UBTTask_WaitBlackboardTime
{
    GENERATED_BODY()

public:
    USandsDPWaitBBTimeAndResetItTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
