// Sands DP. All Rights Reserved

#include "SandsDPGameModeBase.h"
#include "Player/SandsDPBaseCharacter.h"
#include "Player/SandsDPPlayerController.h"
#include "UI/SandsDPGameHUD.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandsDPGameModeBase, All, All);

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

    UE_LOG(LogSandsDPGameModeBase, Display, TEXT("Match State changed"));

    // setting to pause game when ESandsDPMatchState::InTacticalPause is in void ASandsDPPlayerController::SetGamePaused()
    if (State == ESandsDPMatchState::InMenuBeforeBattlePause)
    {
        if (!GetWorld() || !GetWorld()->GetAuthGameMode())
            return;

        auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (!Controller)
            return;

        Controller->SetPause(true);
    }
}
