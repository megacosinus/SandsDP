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

class USandsDPHealthComponent;
class USandsDPWeaponComponent;
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
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USandsDPHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USandsDPWeaponComponent* WeaponComponent;

    // only for debug:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 5.0f;

    virtual void BeginPlay() override;

    void OnHealthChanged(float Health, float HealthDelta);
    void OnDeath();
};
