// Sands DP. All Rights Reserved

#include "AI/Tasks/SandsDPWaitBBTimeAndResetItTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"

USandsDPWaitBBTimeAndResetItTask::USandsDPWaitBBTimeAndResetItTask()
{
    NodeName = "Wait BB Time And Reset";
}

EBTNodeResult::Type USandsDPWaitBBTimeAndResetItTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    Super::ExecuteTask(OwnerComp, NodeMemory);

    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (Blackboard && BlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
    {
        Blackboard->SetValueAsFloat(BlackboardKey.SelectedKeyName, 0.0f);
    }

    return EBTNodeResult::InProgress;
}
