// Sands DP. All Rights Reserved

#include "AI/SandsDPAIControllerGlobal.h"
#include "AI/SandsDPAICharacterGlobal.h"

void ASandsDPAIControllerGlobal::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASandsDPAICharacterGlobal>(InPawn);

    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}
