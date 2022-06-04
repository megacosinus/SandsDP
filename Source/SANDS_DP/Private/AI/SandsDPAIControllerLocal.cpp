// Sands DP. All Rights Reserved

#include "AI/SandsDPAIControllerLocal.h"
#include "AI/SandsDPAICharacterLocal.h"

void ASandsDPAIControllerLocal::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASandsDPAICharacterLocal>(InPawn);

    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}
