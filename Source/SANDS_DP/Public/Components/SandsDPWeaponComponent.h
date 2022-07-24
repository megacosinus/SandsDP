// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SandsDPWeaponComponent.generated.h"

class ASandsDPBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SANDS_DP_API USandsDPWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USandsDPWeaponComponent();

    void Fire();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASandsDPBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponSocket";

private:
    UPROPERTY()
    ASandsDPBaseWeapon* CurrentWeapon = nullptr;

    void SpawnWeapon();
};
