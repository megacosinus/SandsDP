// Sands DP. All Rights Reserved

#include "AI/EQS/SandsDPCoverPointsGenerator.h"
#include "Player/SandsDPPlayerCharacter.h"
#include "Math/Rotator.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

void USandsDPCoverPointsGenerator::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
    if (!GetWorld())
        return;

    const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player)
        return;

    const UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!navSys)
        return;

    TArray<FNavLocation> LocationSet; // local array, where we will all locations where we can hide
    LocationSet.Empty();
    for (float Angle = 0.0; Angle < 359.0f; Angle = Angle + (360.0f / NumberOfRays))
    {
        FVector RotationVector = FVector(Radius, 0.0f, 0.0f);
        FVector ZAxisRotatedVector = RotationVector.RotateAngleAxis(Angle, FVector(0.0f, 0.0f, 1.0f));
        FVector EndPoint = Player->GetActorLocation();
        FVector StartPoint = ZAxisRotatedVector + EndPoint;

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.bReturnPhysicalMaterial = true;
        CollisionParams.AddIgnoredActor(Cast<ASandsDPPlayerCharacter>(Player)); // ignore player

        GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);
        if (HitResult.bBlockingHit)
        {
            FNavLocation NavLoc = FNavLocation(HitResult.ImpactPoint + (HitResult.ImpactNormal * DistanceFromCover) + FVector(0.0f, 0.0f, PointHeight));
            LocationSet.Add(NavLoc);
        }
    }
    // Projects all the nav points into our Viewport and removes those outside of our navmesh
    ProjectAndFilterNavPoints(LocationSet, QueryInstance);

    // Store the generated points as the result of our Query
    StoreNavPoints(LocationSet, QueryInstance);
}

UWorld* USandsDPCoverPointsGenerator::GetWorld() const
{
    if (!HasAnyFlags(RF_ClassDefaultObject))
    {
        return GetOuter()->GetWorld();
    }
    else
    {
        return nullptr;
    }
}
