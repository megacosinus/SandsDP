// Sands DP. All Rights Reserved

#include "AI/Services/SandsDPFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SandsDPAIPerceptionComponent.h"
#include "GameFramework/Actor.h"
#include "SandsDPUtils.h"

USandsDPFindEnemyService::USandsDPFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USandsDPFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        // const auto PerceptionComponent = SandsDPUtils::GetSandsDPPlayerComponent<USandsDPAIPerceptionComponent>(Controller);
        const auto PerceptionComponent = Controller->FindComponentByClass<USandsDPAIPerceptionComponent>(); // try to use engine native template
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
