// Sands DP. All Rights Reserved

#include "AI/SandsDPAICharacterLocal.h"
#include "AI/SandsDPAIControllerLocal.h"
#include "Weapons/SandsDPBaseWeapon.h"

ASandsDPAICharacterLocal::ASandsDPAICharacterLocal() {}

void ASandsDPAICharacterLocal::BeginPlay()
{
    Super::BeginPlay();

    const auto AIController = Cast<ASandsDPAIControllerLocal>(Controller);

    if (!AIController)
        return;

    if (SDPTeamAttitude == ESDPTeamAttitude::Ally)
    {
        AIController->SetTeam(1);
    }
    else if (SDPTeamAttitude == ESDPTeamAttitude::Enemy)
    {
        AIController->SetTeam(2);
    }

    SpawnWeapon();
}

void ASandsDPAICharacterLocal::SpawnWeapon()
{
    if (!GetWorld())
        return;

    const auto Weapon = GetWorld()->SpawnActor<ASandsDPBaseWeapon>(WeaponClass);
    if (Weapon)
    {
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); // simulation physical bodies to false
        Weapon->AttachToComponent(GetMesh(), AttachmentRules, "WeaponSocket");
    }
}
