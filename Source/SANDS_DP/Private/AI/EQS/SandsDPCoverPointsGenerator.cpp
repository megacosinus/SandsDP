// Sands DP. All Rights Reserved

#include "AI/EQS/SandsDPCoverPointsGenerator.h"
#include "Player/SandsDPPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Math/Rotator.h"
#include "Kismet/GameplayStatics.h"

void USandsDPCoverPointsGenerator::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if (!Blackboard)
        return;

    const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);

    const auto Enemy = Cast<AActor>(ContextActor);
    if (!Enemy)
        return;

    TArray<FNavLocation> LocationSet; // local array, where we will put all locations where we can hide
    LocationSet.Empty();
    for (float Angle = 0.0; Angle < 359.0f; Angle = Angle + (360.0f / NumberOfRays))
    {
        FVector RotationVector = FVector(Radius, 0.0f, 0.0f);
        FVector ZAxisRotatedVector = RotationVector.RotateAngleAxis(Angle, FVector(0.0f, 0.0f, 1.0f));
        FVector EndPoint = Enemy->GetActorLocation();
        FVector StartPoint = ZAxisRotatedVector + EndPoint;

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.bReturnPhysicalMaterial = true;
        CollisionParams.AddIgnoredActor(Cast<ASandsDPPlayerCharacter>(Enemy)); // ignore enemy

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