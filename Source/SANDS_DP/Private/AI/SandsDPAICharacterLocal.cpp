// Sands DP. All Rights Reserved

#include "AI/SandsDPAICharacterLocal.h"
#include "AI/SandsDPAIControllerLocal.h"
#include "Weapons/SandsDPBaseWeapon.h"
#include "Components/SandsDPHealthComponent.h"
#include "Components/SandsDPWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(AICharacter, All, All);

ASandsDPAICharacterLocal::ASandsDPAICharacterLocal()
{
    HealthComponent = CreateDefaultSubobject<USandsDPHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USandsDPWeaponComponent>("WeaponComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent"); // for debug
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

void ASandsDPAICharacterLocal::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(WeaponComponent);
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

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ThisClass::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ThisClass::OnHealthChanged);
}

void ASandsDPAICharacterLocal::OnHealthChanged(float Health, float HealthDelta)
{
    // for debug:
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASandsDPAICharacterLocal::OnDeath()
{
    UE_LOG(AICharacter, Display, TEXT("Player %s is dead"), *GetName());

    // PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}
