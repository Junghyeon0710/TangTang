// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TangTang : ModuleRules
{
	public TangTang(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule","UMG", "Niagara" });
	}
}
