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

class ASandsDPBaseWeapon;
class USandsDPHealthComponent;
class UTextRenderComponent;

UCLASS()
class SANDS_DP_API ASandsDPAICharacterLocal : public ASandsDPAICharacter
{
    GENERATED_BODY()

public:
    ASandsDPAICharacterLocal();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    ESDPTeamAttitude SDPTeamAttitude = ESDPTeamAttitude::Ally;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASandsDPBaseWeapon> WeaponClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USandsDPHealthComponent* HealthComponent;

    // only for debug:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    virtual void BeginPlay() override;

private:
    void SpawnWeapon();
};
