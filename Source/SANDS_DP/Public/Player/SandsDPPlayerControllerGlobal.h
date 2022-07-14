// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/SandsDPPlayerController.h"
#include "SandsDPPlayerControllerGlobal.generated.h"

class ASandsDPGlobalCharacter;
class USpringArmComponent;
UCLASS()
class SANDS_DP_API ASandsDPPlayerControllerGlobal : public ASandsDPPlayerController
{
    GENERATED_BODY()

public:
    ASandsDPPlayerControllerGlobal();

protected:
    virtual void SetupInputComponent() override;

private:
    void YawCamera(float AxisValue);
    void PitchCamera(float AxisValue);
    bool bCameraView = false;
    ASandsDPGlobalCharacter* PlayerCharacter;
    USpringArmComponent* SpringArm;
    void StartCameraRotation();
    void StopCameraRotation();
};
