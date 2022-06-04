// Sands DP. All Rights Reserved

#include "SandsDPGameModeLocal.h"
#include "Player/SandsDPLocalCharacter.h"
#include "Player/SandsDPPlayerControllerLocal.h"
#include "UI/SandsDPGameHUD.h"

ASandsDPGameModeLocal::ASandsDPGameModeLocal()
{
    DefaultPawnClass = ASandsDPLocalCharacter::StaticClass();
    PlayerControllerClass = ASandsDPPlayerControllerLocal::StaticClass();
    HUDClass = ASandsDPGameHUD::StaticClass();
}

void ASandsDPGameModeLocal::StartPlay()
{
    Super::StartPlay();

    SetMatchState(ESandsDPMatchState::InBattle);
}
