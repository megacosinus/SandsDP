// Sands DP. All Rights Reserved

#include "AI/SandsDPAICharacter.h"
#include "AI/SandsDPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASandsDPAICharacter::ASandsDPAICharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASandsDPAIController::StaticClass();

    // This code is for smooth rotation AI character:
    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
    }
    // End of code for smooth rotation AI character.
}
