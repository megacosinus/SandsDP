// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SandsDPBaseWidget.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
};
