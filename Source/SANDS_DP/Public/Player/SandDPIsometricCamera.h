// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandDPIsometricCamera.generated.h"

UCLASS()
class SANDS_DP_API ASandDPIsometricCamera : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ASandDPIsometricCamera();

    /** Returns TopDownCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns CursorToWorld subobject **/

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom; // Adding Springarm to Base Character

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* TopDownCameraComponent; // Adding Camera to Base Character

    void MoveRight(float Value);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
