// Sands DP. All Rights Reserved

#include "Components/SandsDPNavigationSplineComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h" // mesh for Navigation Path
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"    // this is for Navigation Path
#include "NavigationPath.h"                                      // and this is for Navigation Path
#include "Components/SplineComponent.h"                          // this is for Navigation Path too
#include "Player/SandsDPBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogNavigationSplineComponent, All, All);

// Sets default values for this component's properties
USandsDPNavigationSplineComponent::USandsDPNavigationSplineComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    auto Character = Cast<ASandsDPBaseCharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    // Creating a spline to showing a Navigation Path
    NavigationSpline = CreateDefaultSubobject<USplineComponent>("NavigationSpline");
    NavigationSpline->SetupAttachment(Character->GetRootComponent());
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

// Called when the game starts
void USandsDPNavigationSplineComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...
}

void USandsDPNavigationSplineComponent::CalculateNavigationPath(FVector WhereToGo)
{
    if (!GetWorld())
        return;

    UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());

    if (!navSys)
        return;

    auto Character = Cast<ASandsDPBaseCharacter>(GetOwner());
    if (!Character)
        return;

    NavigationPath = navSys->FindPathToLocationSynchronously(GetWorld(), Character->GetRootComponent()->GetComponentLocation(), WhereToGo, NULL);
    if (NavigationPath && NavigationPath->GetPathLength() > DistanceBetweenPoints - 1)
    {
        DrawNavigationSpline();
    }
}

void USandsDPNavigationSplineComponent::DrawNavigationSpline()
{
    TArray<FVector> VectorOldPoints = {};

    UE_LOG(LogNavigationSplineComponent, Display, TEXT("Navigation Path points: %i"), NavigationPath->PathPoints.Num());

    NavigationSpline->SetSplinePoints(NavigationPath->PathPoints, ESplineCoordinateSpace::World); // Set the spline points to be the same as the navigation path
    for (int i = 0; i < NavigationPath->PathPoints.Num(); i++)
    {
        float Distance = NavigationSpline->GetDistanceAlongSplineAtSplinePoint(i);
        VectorOldPoints.Push(NavigationPath->PathPoints[i]); // Remember this point's world location
        if (Distance > 1000000.f)
        {
            break; // Stop checking if this point is too far away from player
        }
    }

    NavigationSpline->SetSplinePoints(VectorOldPoints, ESplineCoordinateSpace::World); // Set and straighten the spline again
    for (int i = 0; i < VectorOldPoints.Num(); i++)
    {
        NavigationSpline->SetTangentAtSplinePoint(i, FVector::ZeroVector, ESplineCoordinateSpace::World);
    }

    DrawNavigationMesh();
}

void USandsDPNavigationSplineComponent::DrawNavigationMesh()
{
    NavigationMesh->ClearInstances();
    NavigationMeshLastPoint->ClearInstances();

    float Length = NavigationSpline->GetSplineLength();
    int NumPoints = FMath::RoundToInt(Length / DistanceBetweenPoints);
    float D = DistanceBetweenPoints;

    // Draw points except last one
    for (int PointIndex = 0; PointIndex < NumPoints - 1; ++PointIndex)
    {
        FVector Location = NavigationSpline->GetLocationAtDistanceAlongSpline((Length - D), ESplineCoordinateSpace::World);
        FTransform Transform(Location);
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
