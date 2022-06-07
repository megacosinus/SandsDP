// Sands DP. All Rights Reserved

#include "Player/SandsDPPlayerControllerGlobal.h"
#include "Player/SandsDPGlobalCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void ASandsDPPlayerControllerGlobal::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("CameraYaw", this, &ASandsDPPlayerControllerGlobal::YawCamera);
    InputComponent->BindAction("RotateCamera", IE_Pressed, this, &ASandsDPPlayerControllerGlobal::StartCameraRotation);
    InputComponent->BindAction("RotateCamera", IE_Released, this, &ASandsDPPlayerControllerGlobal::StopCameraRotation);
}

void ASandsDPPlayerControllerGlobal::YawCamera(float AxisValue)
{
    if (bCameraView)
    {
        FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
        NewRotation.Yaw += AxisValue;

        if (!GetPawn())
            return;

        auto PlayerCharacter = Cast<ASandsDPGlobalCharacter>(GetPawn());
        if (!PlayerCharacter)
            return;
        auto SpringArm = PlayerCharacter->GetCameraBoom();
        if (!SpringArm)
            return;
        // SringArm->AddLocalRotation(NewRotation);
        SpringArm->AddWorldRotation(NewRotation);
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
