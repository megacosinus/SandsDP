// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/SandsDPBaseWidget.h"
#include "SandsDPMenuBeforeBattleWidget.generated.h"

class UButton;

UCLASS()
class SANDS_DP_API USandsDPMenuBeforeBattleWidget : public USandsDPBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ToTheBattleButton;

    UPROPERTY(meta = (BindWidget))
    UButton* RetreatButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FName LevelName;

private:
    UFUNCTION()
    void ToTheBattle();

    UFUNCTION()
    void OnRetreat();
};
