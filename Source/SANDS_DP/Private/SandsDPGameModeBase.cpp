// Sands DP. All Rights Reserved

#include "SandsDPGameModeBase.h"
#include "Player/SandsDPBaseCharacter.h"
#include "Player/SandsDPPlayerController.h"
#include "UI/SandsDPGameHUD.h"

ASandsDPGameModeBase::ASandsDPGameModeBase()
{
    DefaultPawnClass = ASandsDPBaseCharacter::StaticClass();
    PlayerControllerClass = ASandsDPPlayerController::StaticClass();
    HUDClass = ASandsDPGameHUD::StaticClass();
}

void ASandsDPGameModeBase::StartPlay()
{
    Super::StartPlay();

    SetMatchState(ESandsDPMatchState::InRealtimeGame);
}

void ASandsDPGameModeBase::SetMatchState(ESandsDPMatchState State)
{
    if (MatchState == State) // if match state not changed
        return;

    MatchState = State;

    // Broadcast about changed match state:
    OnMatchStateChanged.Broadcast(MatchState);
}
