// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class cavrnus_cvt_53 : ModuleRules
{
	public cavrnus_cvt_53(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities", "Slate", "SlateCore", "zlib"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Archive"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Archive/ZipUtilities"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Archive/ZipUtilities/ThirdParty"));

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
