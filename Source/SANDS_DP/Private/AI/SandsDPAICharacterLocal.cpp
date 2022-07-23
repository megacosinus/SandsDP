// Sands DP. All Rights Reserved

#include "AI/SandsDPAICharacterLocal.h"
#include "AI/SandsDPAIControllerLocal.h"
#include "Weapons/SandsDPBaseWeapon.h"
#include "Components/SandsDPHealthComponent.h"
#include "Components/TextRenderComponent.h"

ASandsDPAICharacterLocal::ASandsDPAICharacterLocal()
{
    HealthComponent = CreateDefaultSubobject<USandsDPHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent"); // for debug
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

void ASandsDPAICharacterLocal::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);

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

    // for debug:
    const auto Health = HealthComponent->GetHealth();
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

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
