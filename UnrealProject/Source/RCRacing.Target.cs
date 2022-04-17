/*
Copyright 2022 Inertial Sketch
Version: 0.2
*/

using UnrealBuildTool;
using System.Collections.Generic;

public class RCRacingTarget : TargetRules
{
	public RCRacingTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("RCRacing");
	}
}
