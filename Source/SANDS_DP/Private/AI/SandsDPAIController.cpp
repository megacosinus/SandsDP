// Sands DP. All Rights Reserved

#include "AI/SandsDPAIController.h"
#include "Components/SandsDPAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASandsDPAIController::ASandsDPAIController()
{
    SandsDPAIPerceptionComponent = CreateDefaultSubobject<USandsDPAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*SandsDPAIPerceptionComponent);
}

void ASandsDPAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASandsDPAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
