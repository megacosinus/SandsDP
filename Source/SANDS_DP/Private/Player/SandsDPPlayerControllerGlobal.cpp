// Sands DP. All Rights Reserved

#include "Player/SandsDPPlayerControllerGlobal.h"
#include "Player/SandsDPGlobalCharacter.h"
#include "GameFramework/SpringArmComponent.h"

ASandsDPPlayerControllerGlobal::ASandsDPPlayerControllerGlobal() {}

void ASandsDPPlayerControllerGlobal::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("CameraYaw", this, &ThisClass::YawCamera);
    InputComponent->BindAxis("CameraPitch", this, &ThisClass::PitchCamera);
    InputComponent->BindAction("RotateCamera", IE_Pressed, this, &ThisClass::StartCameraRotation);
    InputComponent->BindAction("RotateCamera", IE_Released, this, &ThisClass::StopCameraRotation);
}

void ASandsDPPlayerControllerGlobal::YawCamera(float AxisValue)
{
    if (bCameraView)
    {
        if (!SpringArm)
            return;
        SpringArm->AddWorldRotation(FRotator(0.0f, AxisValue, 0.0f));
    }
}

void ASandsDPPlayerControllerGlobal::PitchCamera(float AxisValue)
{
    if (bCameraView)
    {
        if (!SpringArm)
            return;
        SpringArm->AddLocalRotation(FRotator(AxisValue, 0.0f, 0.0f));
    }
}

void ASandsDPPlayerControllerGlobal::StartCameraRotation()
{
    bCameraView = true;
    if (SpringArm)
        return; // if we already have Spring Arm, then no need to get new one
    if (!GetPawn())
        return;
    PlayerCharacter = Cast<ASandsDPGlobalCharacter>(GetPawn());
    if (!PlayerCharacter)
        return;
    SpringArm = PlayerCharacter->GetCameraBoom();
}

void ASandsDPPlayerControllerGlobal::StopCameraRotation()
{
    bCameraView = false;
}
