// Sands DP. All Rights Reserved

#include "Components/SandsDPWeaponComponent.h"
#include "Weapons/SandsDPBaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USandsDPWeaponComponent::USandsDPWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USandsDPWeaponComponent::Fire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->Fire();
}

// Called when the game starts
void USandsDPWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void USandsDPWeaponComponent::SpawnWeapon()
{
    if (!GetWorld())
        return;

    auto Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    CurrentWeapon = GetWorld()->SpawnActor<ASandsDPBaseWeapon>(WeaponClass);
    if (!CurrentWeapon)
        return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); // simulation physical bodies to false
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}