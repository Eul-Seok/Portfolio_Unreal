// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestCpp1 : ModuleRules
{
	public TestCpp1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem", "AIModule", "GamePlayTasks", "LevelSequence", "MovieScene" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
