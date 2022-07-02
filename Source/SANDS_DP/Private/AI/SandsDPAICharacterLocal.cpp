// Sands DP. All Rights Reserved

#include "AI/SandsDPAICharacterLocal.h"
#include "AI/SandsDPAIControllerLocal.h"

ASandsDPAICharacterLocal::ASandsDPAICharacterLocal() {}

void ASandsDPAICharacterLocal::BeginPlay()
{
    Super::BeginPlay();

    const auto AIController = Cast<ASandsDPAIControllerLocal>(Controller);

    if (!AIController)
        return;

    if (SDPTeamAttitude == ESDPTeamAttitude::Ally)
    {
        AIController->SetTeam(1);
    }
    else if (SDPTeamAttitude == ESDPTeamAttitude::Enemy)
    {
        AIController->SetTeam(2);
    }
}
