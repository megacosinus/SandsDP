// Sands DP. All Rights Reserved

#include "AI/SandsDPAIController.h"
#include "AI/SandsDPAICharacter.h"
#include "Components/SandsDPAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASandsDPAIController::ASandsDPAIController()
{
    SandsDPAIPerceptionComponent = CreateDefaultSubobject<USandsDPAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*SandsDPAIPerceptionComponent);
}

void ASandsDPAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASandsDPAICharacter>(InPawn);

    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
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
