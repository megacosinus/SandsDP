// Sands DP. All Rights Reserved

#include "Components/SandsDPHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "SandsDPGameModeLocal.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
USandsDPHealthComponent::USandsDPHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USandsDPHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &ThisClass::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &ThisClass::OnTakeRadialDamage);
    }
}

void USandsDPHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
    FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    // UE_LOG(LogHealthComponent, Display, TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage, FinalDamage,
    // *BoneName.ToString());
    ApplyDamage(FinalDamage, InstigatedBy);
}

void USandsDPHealthComponent::OnTakeRadialDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser)
{
    // UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
    ApplyDamage(Damage, InstigatedBy);
}

void USandsDPHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    // UE_LOG(LogHealthComponent, Display, TEXT("On any damage: %f"), Damage);
}

void USandsDPHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    SetHealth(Health - Damage);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }

    ReportDamageEvent(Damage, InstigatedBy);
}

void USandsDPHealthComponent::Killed(AController* KillerController)
{
    if (!GetWorld())
        return;

    const auto GameMode = Cast<ASandsDPGameModeLocal>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    // GameMode->Killed(KillerController, VictimController); @todo
}

void USandsDPHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

float USandsDPHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    // const auto Character = Cast<ACharacter>(DamagedActor);
    // if (!Character ||            //
    //     !Character->GetMesh() || //
    //     !Character->GetMesh()->GetBodyInstance(BoneName))
    //     return 1.0f;

    // const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    // if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial))
    //     return 1.0f;

    // return DamageModifiers[PhysMaterial];

    return 1.0f;
}

void USandsDPHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
    if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
        return;

    UAISense_Damage::ReportDamageEvent(GetWorld(),   //
        GetOwner(),                                  //
        InstigatedBy->GetPawn(),                     //
        Damage,                                      //
        InstigatedBy->GetPawn()->GetActorLocation(), //
        GetOwner()->GetActorLocation());
}
