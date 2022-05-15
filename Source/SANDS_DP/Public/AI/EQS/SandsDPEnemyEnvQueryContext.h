// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SandsDPEnemyEnvQueryContext.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API USandsDPEnemyEnvQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()

public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    FName EnemyActorKeyName = "EnemyActor";
};
