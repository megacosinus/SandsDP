// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AI/SandsDPAICharacter.h"
#include "SandsDPAICharacterLocal.generated.h"

UENUM(BlueprintType)
enum class ESDPTeamAttitude : uint8
{
    Ally = 0,
    Enemy
};

UCLASS()
class SANDS_DP_API ASandsDPAICharacterLocal : public ASandsDPAICharacter
{
    GENERATED_BODY()

public:
    ASandsDPAICharacterLocal();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    ESDPTeamAttitude SDPTeamAttitude = ESDPTeamAttitude::Ally;

protected:
    virtual void BeginPlay() override;
};
