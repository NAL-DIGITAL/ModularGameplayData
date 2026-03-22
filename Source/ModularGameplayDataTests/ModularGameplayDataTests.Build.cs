using UnrealBuildTool;

public class ModularGameplayDataTests : ModuleRules
{
	public ModularGameplayDataTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"ModularGameplay",
				"ModularGameplayData",
				"ModularGameplayActors",
				"EnhancedInput",
				"GameFeatures",
			}
		);
	}
}
