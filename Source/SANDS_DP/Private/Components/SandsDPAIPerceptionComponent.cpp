// Sands DP. All Rights Reserved

#include "Components/SandsDPAIPerceptionComponent.h"
#include "AIController.h"
#include "SandsDPUtils.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* USandsDPAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors; // local array, where we will put all Sight actors
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
    {
        // GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors); // если никого не видем, то ищем, кто нас задамажил
        // if (PercieveActors.Num() == 0)                                               // а если и таких нет, то:
        return nullptr;
    }

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT; // maximum float form macros
    AActor* BestPawn = nullptr;

    for (const auto PercieveActor : PercieveActors)
    {
        // const auto HealthComponent = SandsDPUtils::GetSandsDPPlayerComponent<USTUHealthComponent>(PercieveActor);

        const auto PercievePawn = Cast<APawn>(PercieveActor);

        const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
        if (CurrentDistance < BestDistance)
        {
            BestDistance = CurrentDistance;
            BestPawn = PercieveActor;
        }
    }

    return BestPawn;
}
