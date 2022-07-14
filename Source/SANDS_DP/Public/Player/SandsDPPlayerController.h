// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandsDPCoreTypes.h"
#include "GenericTeamAgentInterface.h"
#include "SandsDPPlayerController.generated.h"

UCLASS()
class SANDS_DP_API ASandsDPPlayerController : public APlayerController, public IGenericTeamAgentInterface
{

    GENERATED_BODY()

public:
    ASandsDPPlayerController();

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (ClampMin = "100.0", ClampMax = "10000.0"), meta = (AllowPrivateAccess = "true"))
    float MinimumCameraBoomLength = 300.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (ClampMin = "100.0", ClampMax = "20000.0"), meta = (AllowPrivateAccess = "true"))
    float MaximumCameraBoomLength = 3000.0f;

    // Implement The Generic Team Interface
    FGenericTeamId TeamId;
    FGenericTeamId GetGenericTeamId() const;

protected:
    bool bCanSetNewLocation = true;

    // Begin PlayerController interface
    virtual void SetupInputComponent() override;
    // End PlayerController interface

    virtual void BeginPlay() override;

    /** Navigate player to the current mouse cursor location. */
    void MoveToMouseCursor();

    /** Navigate player to the current touch location. */
    void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

    /** Navigate player to the given world location. */
    void SetNewMoveDestination(const FVector DestLocation);

    /** Input handlers for SetDestination action. */
    void OnSetDestinationPressed();
    void OnSetDestinationReleased();

    void ZoomIn();
    void ZoomOut();

    void SetGamePaused();

private:
    void OnMatchStateChanged(ESandsDPMatchState State);
};
