// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WFCPlayground : ModuleRules
{
	public WFCPlayground(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		// PCHUsage = PCHUsageMode.NoSharedPCHs;
		// PrivatePCHHeaderFile = "$pch.h";
		CppStandard = CppStandardVersion.Cpp17;
		
		// PublicIncludePaths.Add("C:/WorkFast/WCF_Playground/WFCPlayground/Source/LibSL");
		bEnableUndefinedIdentifierWarnings = false;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","WFC"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
