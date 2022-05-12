// Sands DP. All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class SANDS_DPTarget : TargetRules
{
	public SANDS_DPTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "SANDS_DP" } );
	}
}
