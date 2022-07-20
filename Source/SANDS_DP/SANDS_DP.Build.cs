// Sands DP. All Rights Reserved

using UnrealBuildTool;

public class SANDS_DP : ModuleRules
{
    public SANDS_DP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "GameplayTasks",
            "NavigationSystem",
            "AIModule",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] {
            "SANDS_DP/Public/Player",
            "SANDS_DP/Public/UI",
            "SANDS_DP/Public/Components",
            "SANDS_DP/Public/AI",
            "SANDS_DP/Public/AI/Tasks",
            "SANDS_DP/Public/AI/Services",
            "SANDS_DP/Public/AI/EQS",
            "SANDS_DP/Public/Weapons"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}