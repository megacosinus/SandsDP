// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/SandsDPPlayerController.h"
#include "SandsDPPlayerControllerGlobal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPPlayerControllerGlobal : public ASandsDPPlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;

private:
    void YawCamera(float AxisValue);
    bool bCameraView = false;
    void StartCameraRotation();
    void StopCameraRotation();
};
