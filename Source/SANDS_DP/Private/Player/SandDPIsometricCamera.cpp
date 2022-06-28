// Sands DP. All Rights Reserved

#include "Player/SandDPIsometricCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
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

    // Creating scene component
    Scene = CreateDefaultSubobject<USceneComponent>("Scene");
    Scene->SetupAttachment(GetRootComponent());

    // Creating a camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom"); // Creating SpringArm
    CameraBoom->SetupAttachment(Scene);                                     // Attaching SpringArm to character
    CameraBoom->SetUsingAbsoluteRotation(true);                             // Don't want arm to rotate when character does
    CameraBoom->bDoCollisionTest = false;                                   // Don't want to pull camera in when it collides with level
    CameraBoom->SetTickableWhenPaused(true);
    CameraBoom->SetWorldRotation(FRotator(0.0f, -36.5f, -45.0f));
    CameraBoom->TargetArmLength = 1000.0f;

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

    InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
}

void ASandDPIsometricCamera::MoveRight(float Value)
{
    if (Value == 0.0f)
        return;
    Scene->SetWorldLocation((Scene->GetComponentLocation()) + FVector(Value * 10.0f, 0.0f, 0.0f));
}