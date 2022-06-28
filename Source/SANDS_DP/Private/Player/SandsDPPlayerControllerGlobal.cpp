// Sands DP. All Rights Reserved

#include "Player/SandsDPPlayerControllerGlobal.h"
#include "Player/SandsDPGlobalCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void ASandsDPPlayerControllerGlobal::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("CameraYaw", this, &ThisClass::YawCamera);
    InputComponent->BindAction("RotateCamera", IE_Pressed, this, &ThisClass::StartCameraRotation);
    InputComponent->BindAction("RotateCamera", IE_Released, this, &ThisClass::StopCameraRotation);
}

void ASandsDPPlayerControllerGlobal::YawCamera(float AxisValue)
{
    if (bCameraView)
    {
        if (!GetPawn())
            return;
        auto PlayerCharacter = Cast<ASandsDPGlobalCharacter>(GetPawn());
        if (!PlayerCharacter)
            return;
        auto SpringArm = PlayerCharacter->GetCameraBoom();
        if (!SpringArm)
            return;
        SpringArm->AddWorldRotation(FRotator(0.0f, AxisValue, 0.0f));
    }
}

void ASandsDPPlayerControllerGlobal::StartCameraRotation()
{
    bCameraView = true;
}

void ASandsDPPlayerControllerGlobal::StopCameraRotation()
{
    bCameraView = false;
}
