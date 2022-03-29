using UnrealBuildTool;
public class OnlineSessionsLite : ModuleRules
{
    public OnlineSessionsLite(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull", "Steamworks" });
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        PrivateDependencyModuleNames.AddRange(new string[] {  });
    }
}
