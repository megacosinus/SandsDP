// Sands DP. All Rights Reserved

#include "SandsDPFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SandsDPWeaponComponent.h"
#include "AI/SandsDPAIControllerLocal.h"

USandsDPFireService::USandsDPFireService()
{
    NodeName = "Fire";
}

void USandsDPFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto AIControllerLocal = Cast<ASandsDPAIControllerLocal>(Controller);

    const bool CanStartShooting = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller && AIControllerLocal)
    {
        const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USandsDPWeaponComponent>();
        if (WeaponComponent)
        {
            if (CanStartShooting)
            {
                if (!AIControllerLocal->Aiming)
                {
                    AIControllerLocal->Aiming = true;
                    WeaponComponent->StartFire();
                }
            }
            else
            {
                AIControllerLocal->Aiming = false;
                WeaponComponent->StopFire();
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
