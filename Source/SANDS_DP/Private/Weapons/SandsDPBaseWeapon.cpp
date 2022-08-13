// Sands DP. All Rights Reserved

#include "Weapons/SandsDPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASandsDPBaseWeapon::ASandsDPBaseWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASandsDPBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponMesh);
}

void ASandsDPBaseWeapon::StartFire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("StartFire!"));

    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASandsDPBaseWeapon::MakeShot, TimeBetweenShots, true);
}

void ASandsDPBaseWeapon::StopFire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("StopFire!"));
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASandsDPBaseWeapon::MakeShot()
{
    if (!GetWorld())
        return;
    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = SocketTransform.GetLocation();
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(SocketTransform.GetRotation().GetForwardVector(), HalfRad); // Random vector from cone
    // const FVector ShootDirection = FMath::VRandCone(GetOwner()->GetActorForwardVector(), HalfRad); // Random vector from cone
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
}

void ASandsDPBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
        return;
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}