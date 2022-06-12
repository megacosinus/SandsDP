// Sands DP. All Rights Reserved

#include "Player/SandsDPPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Player/SandsDPPlayerCharacter.h"
#include "Engine/World.h"
#include "SandsDPGameModeBase.h"

ASandsDPPlayerController::ASandsDPPlayerController()
{
    bShowMouseCursor = true;
    bShouldPerformFullTickWhenPaused = true;
    if (GetWorld())
        GetWorld()->bIsCameraMoveableWhenPaused = true; // Prevent bluring camera when paused
}

void ASandsDPPlayerController::SetupInputComponent()
{
    // set up gameplay key bindings
    Super::SetupInputComponent();
    if (!InputComponent)
        return;

    InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASandsDPPlayerController::OnSetDestinationPressed);
    InputComponent->BindAction("SetDestination", IE_Released, this, &ASandsDPPlayerController::OnSetDestinationReleased);

    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ASandsDPPlayerController::ZoomIn);
    InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ASandsDPPlayerController::ZoomOut);

    InputComponent->BindAction("Pause", IE_Pressed, this, &ASandsDPPlayerController::SetGamePaused);

    // support touch devices
    InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASandsDPPlayerController::MoveToTouchLocation);
    InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASandsDPPlayerController::MoveToTouchLocation);
}

void ASandsDPPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        if (const auto GameMode = Cast<ASandsDPGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASandsDPPlayerController::OnMatchStateChanged);
        }
    }
}

void ASandsDPPlayerController::MoveToMouseCursor()
{

    // Trace to see what is under the mouse cursor
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        // We hit something, move there
        SetNewMoveDestination(Hit.ImpactPoint);
    }
}

void ASandsDPPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    FVector2D ScreenSpaceLocation(Location);

    // Trace to see what is under the touch location
    FHitResult HitResult;
    GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
    if (HitResult.bBlockingHit)
    {
        // We hit something, move there
        SetNewMoveDestination(HitResult.ImpactPoint);
    }
}

void ASandsDPPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
    if (!GetPawn())
        return;

    float const Distance = FVector::Dist(DestLocation, GetPawn()->GetActorLocation());

    if ((Distance > 120.0f))
    {
        // flag for drawing navigation line
        auto DPPlayerCharacter = Cast<ASandsDPPlayerCharacter>(GetPawn());
        if (!DPPlayerCharacter)
            return;
        DPPlayerCharacter->NewNavigationPoint(DestLocation);

        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
    }
}

void ASandsDPPlayerController::OnSetDestinationPressed()
{
    if (bCanSetNewLocation)
    {
        bCanSetNewLocation = false;
        MoveToMouseCursor();
    }
}

void ASandsDPPlayerController::OnSetDestinationReleased()
{
    bCanSetNewLocation = true;
}

void ASandsDPPlayerController::ZoomIn()
{
    if (GetPawn())
    {
        auto DPPlayerCharacter = Cast<ASandsDPPlayerCharacter>(GetPawn());
        if (!DPPlayerCharacter)
            return;
        USpringArmComponent* CameraBoom = DPPlayerCharacter->GetCameraBoom();
        if (!CameraBoom)
            return;
        float const CameraBoomLength = CameraBoom->TargetArmLength;
        float const NewCameraBoomLength = FMath::Clamp((CameraBoomLength + 100.0f), MinimumCameraBoomLength, MaximumCameraBoomLength);
        CameraBoom->TargetArmLength = (NewCameraBoomLength);
    }
}

void ASandsDPPlayerController::ZoomOut()
{
    if (GetPawn())
    {
        auto DPPlayerCharacter = Cast<ASandsDPPlayerCharacter>(GetPawn());
        if (!DPPlayerCharacter)
            return;
        USpringArmComponent* CameraBoom = DPPlayerCharacter->GetCameraBoom();
        if (!CameraBoom)
            return;
        float const CameraBoomLength = CameraBoom->TargetArmLength;
        float const NewCameraBoomLength = FMath::Clamp((CameraBoomLength - 100.0f), MinimumCameraBoomLength, MaximumCameraBoomLength);
        CameraBoom->TargetArmLength = (NewCameraBoomLength);
    }
}

void ASandsDPPlayerController::SetGamePaused()
{
    static bool bIsPaused = 0;
    bIsPaused = !bIsPaused;

    SetPause(bIsPaused);

    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    const auto GameMode = Cast<ASandsDPGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->SetMatchState(bIsPaused ? ESandsDPMatchState::InTacticalPause : ESandsDPMatchState::InRealtimeGame);
    }
}

void ASandsDPPlayerController::OnMatchStateChanged(ESandsDPMatchState State)
{
    // @TODO need to make it work:
    /*if (State != ESandsDPMatchState::InRealtimeGame || State != ESandsDPMatchState::InTacticalPause)
    {
        SetInputMode(FInputModeUIOnly());
    }
    else
    {
        SetInputMode(FInputModeGameAndUI());
    }*/
}
