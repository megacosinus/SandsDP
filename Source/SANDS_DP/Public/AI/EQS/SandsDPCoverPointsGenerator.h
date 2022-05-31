// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "SandsDPCoverPointsGenerator.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPCoverPointsGenerator : public UEnvQueryGenerator_ProjectedPoints
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float Radius = 2000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float PointHeight = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (ClampMin = "1.0", ClampMax = "360.0"))
    float NumberOfRays = 36.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (ClampMin = "30.0", ClampMax = "500.0"))
    float DistanceFromCover = 50.0f;

    virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

    virtual class UWorld* GetWorld() const override;
};
