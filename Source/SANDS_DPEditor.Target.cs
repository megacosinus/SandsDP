// Sands DP. All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class SANDS_DPEditorTarget : TargetRules
{
	public SANDS_DPEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "SANDS_DP" } );
	}
}
