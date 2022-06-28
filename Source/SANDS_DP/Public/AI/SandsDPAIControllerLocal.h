// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AI/SandsDPAIController.h"
#include "SandsDPAIControllerLocal.generated.h"

/**
 *
 */
UCLASS()
class SANDS_DP_API ASandsDPAIControllerLocal : public ASandsDPAIController
{
    GENERATED_BODY()

public:
    //    void SetTeamID(uint8 TeamID) { SetGenericTeamId(FGenericTeamId(TeamID)); }

    FGenericTeamId TeamId;

    FTimerHandle TeamIDHandle;

    UFUNCTION(BlueprintCallable, DisplayName = "SetTeamID", Category = "AI")
    void SetTeam(uint8 const& id) { TeamId = FGenericTeamId(id); }

    FGenericTeamId GetGenericTeamId() const override { return TeamId; }

    ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    void LogTeamNumber();

protected:
    virtual void OnPossess(APawn* InPawn) override;
};
