// Sands DP. All Rights Reserved

#include "UI/SandsDPMenuBeforeBattleWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"
#include "GameFramework/Actor.h"
#include "Player/SandsDPPlayerController.h"
#include "Player/SandsDPPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SandsDPGameModeBase.h"

bool USandsDPMenuBeforeBattleWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (RetreatButton)
    {
        RetreatButton->OnClicked.AddDynamic(this, &USandsDPMenuBeforeBattleWidget::OnRetreat);
    }

    return InitStatus;
}

void USandsDPMenuBeforeBattleWidget::OnRetreat()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!Controller)
        return;

    Controller->SetPause(false);

    const auto GameMode = Cast<ASandsDPGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->SetMatchState(ESandsDPMatchState::InRealtimeGame);
    }
}
