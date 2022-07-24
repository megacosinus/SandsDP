// Sands DP. All Rights Reserved

#include "Weapons/SandsDPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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
}

void ASandsDPBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
}