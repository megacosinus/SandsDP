// Sands DP. All Rights Reserved

#include "SandsDPGameModeGlobal.h"
#include "Player/SandsDPPlayerCharacter.h" // name must be SandsDPGlobalCharacter
#include "Player/SandsDPPlayerControllerGlobal.h"
#include "UI/SandsDPGameHUD.h"

ASandsDPGameModeGlobal::ASandsDPGameModeGlobal()
{
    DefaultPawnClass = ASandsDPPlayerCharacter::StaticClass();
    PlayerControllerClass = ASandsDPPlayerControllerGlobal::StaticClass();
    HUDClass = ASandsDPGameHUD::StaticClass();
}

void ASandsDPGameModeGlobal::StartPlay()
{
    Super::StartPlay();

    SetMatchState(ESandsDPMatchState::InRealtimeGame);
}
