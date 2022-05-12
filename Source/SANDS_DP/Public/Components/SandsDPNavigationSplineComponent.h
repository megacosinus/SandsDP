// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SandsDPNavigationSplineComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SANDS_DP_API USandsDPNavigationSplineComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USandsDPNavigationSplineComponent();

    void SetCalculationNavigationPath(FVector WhereToGo) { CalculateNavigationPath(WhereToGo); }

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class USplineComponent* NavigationSpline; // A spline that uses to show navigation path

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class UNavigationPath* NavigationPath;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    float DistanceBetweenPoints = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class UHierarchicalInstancedStaticMeshComponent* NavigationMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NavigatioPath, meta = (AllowPrivateAccess = "true"))
    class UHierarchicalInstancedStaticMeshComponent* NavigationMeshLastPoint;

protected:
    /** Drawing Navigation Spline */
    void CalculateNavigationPath(FVector WhereToGo);
    void DrawNavigationSpline();
    void DrawNavigationMesh();
};
