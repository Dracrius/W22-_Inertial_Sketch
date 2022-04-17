/*
Copyright 2022 Inertial Sketch
Version: 0.2
*/

using UnrealBuildTool;
using System.Collections.Generic;

public class RCRacingEditorTarget : TargetRules
{
	public RCRacingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("RCRacing");
	}
}
