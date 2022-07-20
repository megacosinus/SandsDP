// Sands DP. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SandsDPBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SANDS_DP_API ASandsDPBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASandsDPBaseWeapon();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
