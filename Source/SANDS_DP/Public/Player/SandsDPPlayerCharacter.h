// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/SandsDPBaseCharacter.h"
#include "Components/SplineMeshComponent.h" // for drawing mesh across the spline
#include "SandsDPPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPPlayerCharacter : public ASandsDPBaseCharacter
{
    GENERATED_BODY()

public:
    ASandsDPPlayerCharacter();

    // Called every frame
    virtual void Tick(float DeltaSecond) override;

    /** Returns TopDownCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns CursorToWorld subobject **/
    FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
    /** Returns CursorToWorld subobject **/
    FORCEINLINE class USandsDPNavigationSplineComponent* GetNavigationSplineComponent() { return NavigationSplineComponent; }
    /** Returns NavigationSpline subobject **/
    FORCEINLINE class USplineComponent* GetNavigationSpline() { return NavigationSpline; }
    /** Returns NavigationMesh subobject **/
    FORCEINLINE class UHierarchicalInstancedStaticMeshComponent* GetNavigationMesh() { return NavigationMesh; }
    /** Returns NavigationMesh subobject **/
    FORCEINLINE class UHierarchicalInstancedStaticMeshComponent* GetNavigationMeshLastPoint() { return NavigationMeshLastPoint; }

    void NewNavigationPoint(FVector WhereToGo);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom; // Adding Springarm to Base Character

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* TopDownCameraComponent; // Adding Camera to Base Character

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UDecalComponent* CursorToWorld; // A decal that point the cursor location

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USandsDPNavigationSplineComponent* NavigationSplineComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class USplineComponent* NavigationSpline; // A spline that uses to show navigation path

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class UNavigationPath* NavigationPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    float DistanceBetweenPoints = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class UHierarchicalInstancedStaticMeshComponent* NavigationMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class UHierarchicalInstancedStaticMeshComponent* NavigationMeshLastPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis; // This is for orienting Mesh across the spline

protected:
    /** Drawing Navigation Spline */
    void CalculateNavigationPath(FVector WhereToGo);
    void DrawNavigationSpline();
    void DrawNavigationMesh();

    FVector CurrentPointLocation = FVector::ZeroVector;
};
