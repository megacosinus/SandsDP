// Sands DP. All Rights Reserved

#include "AI/EQS/SandsDPEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USandsDPEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get()); // character which owns this EQS

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if (!Blackboard)
        return;

    const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName); // returns UObject. Need Cast to AACtor
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
