/*
Copyright 2022 Inertial Sketch
Version: 0.2
*/

using UnrealBuildTool;

public class RCRacing : ModuleRules
{
	public RCRacing(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysXVehicles", "HeadMountedDisplay", "PhysicsCore", "OnlineSessionsLite" });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
