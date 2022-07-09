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

    SetGenericTeamId(FGenericTeamId(2));
}

ETeamAttitude::Type ASandsDPAIControllerGlobal::GetTeamAttitudeTowards(const AActor& Other) const
{
    const auto OtherPawn = Cast<APawn>(&Other);

    if (!OtherPawn)
        return ETeamAttitude::Neutral;

    const auto TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

    if (!TeamAgent)
        return ETeamAttitude::Neutral;

    return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
}
