// Sands DP. All Rights Reserved

#include "UI/SandsDPGameHUD.h"
#include "UI/SandsDPBaseWidget.h"
#include "SandsDPGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ASandsDPGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void ASandsDPGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ESandsDPMatchState::InRealtimeGame, CreateWidget<USandsDPBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESandsDPMatchState::InTacticalPause, CreateWidget<USandsDPBaseWidget>(GetWorld(), TacticalPauseWidgetClass));
    GameWidgets.Add(ESandsDPMatchState::InMenuBeforeBattlePause, CreateWidget<USandsDPBaseWidget>(GetWorld(), MenuBeforeBattleWidgetClass));

    // add every widget into viewport and make them hidden:
    for (auto GameWidgetPair : GameWidgets)
    {
        // every element of TMAP have TPAIR
        const auto GameWidget = GameWidgetPair.Value; // raw pointer to UserWidget
        if (!GameWidget)
            continue;
        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ASandsDPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASandsDPGameHUD::OnMatchStateChanged);
        }
    }
}

void ASandsDPGameHUD::OnMatchStateChanged(ESandsDPMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }

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
