// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SandsDPAIController.generated.h"

class USandsDPAIPerceptionComponent;

UCLASS() class SANDS_DP_API ASandsDPAIController : public AAIController
{
    GENERATED_BODY()

public:
    ASandsDPAIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USandsDPAIPerceptionComponent* SandsDPAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;

    virtual void Tick(float DeltaTime) override;

private:
    AActor* GetFocusOnActor() const;
};
