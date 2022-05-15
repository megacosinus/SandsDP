// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SandsDPCoreTypes.h"
#include "SandsDPGameHUD.generated.h"

class USandsDPBaseWidget;

UCLASS()
class SANDS_DP_API ASandsDPGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> TacticalPauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuBeforeBattleWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESandsDPMatchState, USandsDPBaseWidget*> GameWidgets;

    UPROPERTY()
    USandsDPBaseWidget* CurrentWidget = nullptr;

private:
    void OnMatchStateChanged(ESandsDPMatchState State);
};
