// Sands DP. All Rights Reserved

#include "AI/Services/SandsDPChkDistToPlayerService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SandsDPAIPerceptionComponent.h"
#include "GameFramework/Actor.h"
#include "SandsDPGameModeBase.h"

USandsDPChkDistToPlayerService::USandsDPChkDistToPlayerService()
{
    NodeName = "Check Distance To Player";
}

void USandsDPChkDistToPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {

        const auto Controller = OwnerComp.GetAIOwner();
        const auto Pawn = Controller->GetPawn();
        if (!Pawn)
            return;

        const auto PerceptionComponent = Controller->FindComponentByClass<USandsDPAIPerceptionComponent>(); // try to use engine native template
        if (PerceptionComponent)
        {
            const auto CurrentDistance = (PerceptionComponent->GetClosestEnemy()->GetActorLocation() - Pawn->GetActorLocation()).Size();

            if (CurrentDistance <= MinimumDistance)
            {
                const auto GameMode = Cast<ASandsDPGameModeBase>(GetWorld()->GetAuthGameMode());
                if (GameMode)
                {
                    GameMode->SetMatchState(StateToTurnOn);
                    Blackboard->SetValueAsFloat(CoolDownTimeKey.SelectedKeyName, CoolDownTime);
                }
            }
            else if (CurrentDistance > MinimumDistance)
            {
                Blackboard->SetValueAsFloat(CoolDownTimeKey.SelectedKeyName, 0.0f);
            }
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
