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
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* RetreatButton;

private:
    UFUNCTION()
    void OnRetreat();
};
