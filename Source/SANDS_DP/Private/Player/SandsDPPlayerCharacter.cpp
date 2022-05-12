// Sands DP. All Rights Reserved

#include "Player/SandsDPPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/SandsDPNavigationSplineComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h" // mesh for Navigation Path
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"    // this is for Navigation Path
#include "NavigationPath.h"                                      // and this is for Navigation Path
#include "Components/SplineComponent.h"                          // this is for Navigation Path too

ASandsDPPlayerCharacter::ASandsDPPlayerCharacter()
{
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

    // Creating a decal in the world to show the cursor's location
    CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
    CursorToWorld->SetupAttachment(RootComponent);
    CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
    CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
    CursorToWorld->SetTickableWhenPaused(true);

    //// Creating component which will show navigation line
    // NavigationSplineComponent = CreateDefaultSubobject<USandsDPNavigationSplineComponent>("NavigationSplineComponent");

    // Creating a spline to showing a Navigation Path
    NavigationSpline = CreateDefaultSubobject<USplineComponent>("NavigationSpline");
    NavigationSpline->SetupAttachment(RootComponent);
    NavigationSpline->SetTickableWhenPaused(true);
    NavigationSpline->ClearSplinePoints(); // Reset the Spline

    // Creating a dots to show a Navigation Path through the spline
    NavigationMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("NavigationMesh"));
    NavigationMesh->NumCustomDataFloats = 1;
    NavigationMesh->SetTickableWhenPaused(true);
    NavigationMeshLastPoint = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("NavigationMeshLastPoint"));
    NavigationMeshLastPoint->NumCustomDataFloats = 1;
    NavigationMeshLastPoint->SetTickableWhenPaused(true);
}

void ASandsDPPlayerCharacter::Tick(float DeltaSecond)
{
    Super::Tick(DeltaSecond);

    if (CursorToWorld != nullptr)
    {
        if (APlayerController* PC = Cast<APlayerController>(GetController()))
        {
            static FVector NavigationPoint = FVector(0.f, 0.f, 0.f); // location where character must go
            FHitResult TraceHitResult;
            PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
            FVector CursorFV = TraceHitResult.ImpactNormal;
            FRotator CursorR = CursorFV.Rotation();
            CursorToWorld->SetWorldLocation(TraceHitResult.Location);
            CursorToWorld->SetWorldRotation(CursorR);

            // don't calculate navigation if navigation point is too close to actor
            float const DistanceToNavPoint = FVector::Dist(CurrentPointLocation, GetActorLocation());

            if ((DistanceToNavPoint < DistanceBetweenPoints - 1.0f))
                return;

            if ((CurrentPointLocation != FVector(0.f, 0.f, 0.f)) && PC->IsPaused() == 0)
            {
                CalculateNavigationPath(CurrentPointLocation);
                // NavigationSplineComponent->SetCalculationNavigationPath(CurrentPointLocation);
            }
        }
    }
}

void ASandsDPPlayerCharacter::NewNavigationPoint(FVector WhereToGo)
{
    if (WhereToGo != CurrentPointLocation)
        CurrentPointLocation = WhereToGo;
}

void ASandsDPPlayerCharacter::CalculateNavigationPath(FVector WhereToGo)
{
    if (!GetWorld())
        return;

    UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());

    if (!navSys)
        return;

    NavigationPath = navSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), WhereToGo, NULL);
    if (NavigationPath && NavigationPath->GetPathLength() > DistanceBetweenPoints - 1)
    {
        DrawNavigationSpline();
    }
    else
    {
        if (NavigationMesh && NavigationMeshLastPoint)
        {
            NavigationMesh->ClearInstances();
            NavigationMeshLastPoint->ClearInstances();
        }
    }
}

void ASandsDPPlayerCharacter::DrawNavigationSpline()
{
    TArray<FVector> VectorOldPoints = {};

    NavigationSpline->SetSplinePoints(NavigationPath->PathPoints, ESplineCoordinateSpace::World); // Set the spline points to be the same as the navigation path
    for (int i = 0; i < NavigationPath->PathPoints.Num(); i++)
    {
        float Distance = NavigationSpline->GetDistanceAlongSplineAtSplinePoint(i);
        if (Distance > 1000000.f)
        {
            break; // Stop checking if this point is too far away from player
        }
        VectorOldPoints.Push(NavigationPath->PathPoints[i]); // Remember this point's world location
    }

    NavigationSpline->SetSplinePoints(VectorOldPoints, ESplineCoordinateSpace::World); // Set and straighten the spline again
    for (int i = 0; i < VectorOldPoints.Num(); i++)
    {
        NavigationSpline->SetTangentAtSplinePoint(i, FVector::ZeroVector, ESplineCoordinateSpace::World);
    }

    DrawNavigationMesh();
}

void ASandsDPPlayerCharacter::DrawNavigationMesh()
{
    NavigationMesh->ClearInstances();
    NavigationMeshLastPoint->ClearInstances();

    float Length = NavigationSpline->GetSplineLength();
    int NumPoints = FMath::RoundToInt(Length / DistanceBetweenPoints);
    float D = DistanceBetweenPoints;

    // This code is for landing Navigatoin Mesh to ground
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());    // ignore player
    CollisionParams.bReturnPhysicalMaterial = true; // передаём физический материал, в который попали
    FHitResult HitResult;

    if (!GetWorld())
        return;

    // Draw points except last one
    for (int PointIndex = 0; PointIndex < NumPoints - 1; ++PointIndex)
    {
        FVector Location = NavigationSpline->GetLocationAtDistanceAlongSpline((Length - D), ESplineCoordinateSpace::World);

        // landing code
        GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + FVector(0.f, 0.f, -1000.f), ECollisionChannel::ECC_Visibility, CollisionParams);

        FVector EndPoint;

        if (HitResult.bBlockingHit)
        {
            EndPoint = HitResult.ImpactPoint;
        }
        else
        {
            GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + FVector(0.f, 0.f, +1000.f), ECollisionChannel::ECC_Visibility, CollisionParams);
            EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : Location;
        }
        // const FVector Direction = (EndPoint - SocketTransform.GetLocation()).GetSafeNormal();
        // end of landing code

        FTransform Transform(EndPoint);
        NavigationMesh->AddInstance(Transform);
        NavigationMesh->SetCustomDataValue(PointIndex, 0, D / Length);

        D += DistanceBetweenPoints;
    }

    // Draw last point
    FVector Location = NavigationSpline->GetLocationAtDistanceAlongSpline(Length, ESplineCoordinateSpace::World);
    FTransform Transform(Location);
    NavigationMeshLastPoint->AddInstance(Transform);
    NavigationMeshLastPoint->SetCustomDataValue(NumPoints, 0, D / Length);
}
