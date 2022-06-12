// Sands DP. All Rights Reserved

#include "Player/SandDPIsometricCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ASandDPIsometricCamera::ASandDPIsometricCamera()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Don't rotate character to camera direction
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Creating a camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom"); // Creating SpringArm
    CameraBoom->SetupAttachment(GetRootComponent());                        // Attaching SpringArm to character
    CameraBoom->SetUsingAbsoluteRotation(true);                             // Don't want arm to rotate when character does
    CameraBoom->bDoCollisionTest = false;                                   // Don't want to pull camera in when it collides with level
    CameraBoom->SetTickableWhenPaused(true);
    // Code for Zooming In and Out in the SandsDPPlayerController

    // Creating a camera
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent"); // Creating Camera
    TopDownCameraComponent->SetupAttachment(CameraBoom);                                         // Attaching Camera to SpringArm
    TopDownCameraComponent->bUsePawnControlRotation = false;                                     // Camera does not rotate relative to arm
    TopDownCameraComponent->SetTickableWhenPaused(true);                                         // Tick camera when paused
}

// Called when the game starts or when spawned
void ASandDPIsometricCamera::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASandDPIsometricCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASandDPIsometricCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAxis("MoveRight", this, &ASandDPIsometricCamera::MoveRight);
}

void ASandDPIsometricCamera::MoveRight(float Value)
{
    if (Value == 0.0f)
        return;
    // CameraBoom->SetRelativeLocation((CameraBoom->GetRelativeLocation()) + FVector(Value, 0.0f, 0.0f));
    TopDownCameraComponent->SetWorldLocation((TopDownCameraComponent->GetComponentLocation()) + FVector(Value * 10.0f, 0.0f, 0.0f));
    // AddMovementInput(GetActorForwardVector(), Value);
}