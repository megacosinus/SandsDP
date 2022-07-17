// Sands DP. All Rights Reserved

#include "Player/SandsDPPlayerControllerLocal.h"

DEFINE_LOG_CATEGORY_STATIC(LogLocalController, All, All);

ASandsDPPlayerControllerLocal::ASandsDPPlayerControllerLocal()
{
    TeamId = FGenericTeamId(255); // to be neutral for AI
    UE_LOG(LogLocalController, Display, TEXT("Team number %d"), static_cast<uint8>(GetGenericTeamId()));
}

FGenericTeamId ASandsDPPlayerControllerLocal::GetGenericTeamId() const
{
    return TeamId;
}
