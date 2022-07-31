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

    virtual void StartFire();
    virtual void StopFire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TimeBetweenShots = 2.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void MakeShot();
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

private:
    FTimerHandle ShotTimerHandle;
};
