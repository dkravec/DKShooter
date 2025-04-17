// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DKShooter : ModuleRules
{
	public DKShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
