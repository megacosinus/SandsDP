// Sands DP. All Rights Reserved

#include "AI/SandsDPAIControllerLocal.h"
#include "AI/SandsDPAICharacterLocal.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIController, All, All);

void ASandsDPAIControllerLocal::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASandsDPAICharacterLocal>(InPawn);

    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }

    // UE_LOG(LogAIController, Display, TEXT("Team number %d"), static_cast<uint8>(GetGenericTeamId()));
}

ETeamAttitude::Type ASandsDPAIControllerLocal::GetTeamAttitudeTowards(const AActor& Other) const
{
    const auto OtherPawn = Cast<APawn>(&Other);

    if (!OtherPawn)
        return ETeamAttitude::Neutral;

    const auto TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

    if (!TeamAgent)
        return ETeamAttitude::Neutral;

    FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();

    if (OtherTeamID == TeamId)
    {
        return ETeamAttitude::Friendly;
    }
    else
    {
        return ETeamAttitude::Hostile;
    }
}