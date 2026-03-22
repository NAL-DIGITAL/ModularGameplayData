#if WITH_DEV_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "GameplayTagContainer.h"
#include "DataAsset/ModularPawnData.h"
#include "DataAsset/ModularInputConfig.h"
#include "DataAsset/ModularGameData.h"
#include "GameFeature/GameFeatureAction_ModularWorldBase.h"
#include "ActorComponent/ModularInputConfigComponent.h"

// ---------------------------------------------------------------------------
// Data Asset Loading
// ---------------------------------------------------------------------------

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularPawnDataCDOTest,
	"UEWorlds.ThirdParty.ModularGameplayData.DataAsset.PawnDataCDO",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularPawnDataCDOTest::RunTest(const FString& Parameters)
{
	const UClass* PawnDataClass = UModularPawnData::StaticClass();
	TestNotNull(TEXT("ModularPawnData StaticClass must exist"), PawnDataClass);
	TestTrue(TEXT("ModularPawnData must derive from UPrimaryDataAsset"),
		PawnDataClass->IsChildOf(UPrimaryDataAsset::StaticClass()));
	TestFalse(TEXT("ModularPawnData must not be abstract"),
		PawnDataClass->HasAnyClassFlags(CLASS_Abstract));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularPawnDataDefaultsTest,
	"UEWorlds.ThirdParty.ModularGameplayData.DataAsset.PawnDataDefaults",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularPawnDataDefaultsTest::RunTest(const FString& Parameters)
{
	UModularPawnData* PawnData = NewObject<UModularPawnData>();
	TestNotNull(TEXT("PawnData instance must be valid"), PawnData);

	// Default PawnClass should be null (unset)
	TestTrue(TEXT("Default PawnClass must be null"),
		PawnData->PawnClass == nullptr);

	// Default InputConfig should be null (unset)
	TestTrue(TEXT("Default InputConfig must be null"),
		PawnData->InputConfig == nullptr);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularGameDataCDOTest,
	"UEWorlds.ThirdParty.ModularGameplayData.DataAsset.GameDataCDO",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularGameDataCDOTest::RunTest(const FString& Parameters)
{
	const UClass* GameDataClass = UModularGameData::StaticClass();
	TestNotNull(TEXT("ModularGameData StaticClass must exist"), GameDataClass);
	TestTrue(TEXT("ModularGameData must derive from UPrimaryDataAsset"),
		GameDataClass->IsChildOf(UPrimaryDataAsset::StaticClass()));

	return true;
}

// ---------------------------------------------------------------------------
// Input Config Binding
// ---------------------------------------------------------------------------

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularInputConfigCDOTest,
	"UEWorlds.ThirdParty.ModularGameplayData.InputConfig.InputConfigCDO",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularInputConfigCDOTest::RunTest(const FString& Parameters)
{
	const UClass* InputConfigClass = UModularInputConfig::StaticClass();
	TestNotNull(TEXT("ModularInputConfig StaticClass must exist"), InputConfigClass);
	TestTrue(TEXT("ModularInputConfig must derive from UDataAsset"),
		InputConfigClass->IsChildOf(UDataAsset::StaticClass()));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularInputConfigEmptyLookupTest,
	"UEWorlds.ThirdParty.ModularGameplayData.InputConfig.EmptyConfigLookup",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularInputConfigEmptyLookupTest::RunTest(const FString& Parameters)
{
	UModularInputConfig* InputConfig = NewObject<UModularInputConfig>();
	TestNotNull(TEXT("InputConfig instance must be valid"), InputConfig);

	// Empty config must return null for any tag lookup
	FGameplayTag InvalidTag;
	const UInputAction* NativeResult = InputConfig->FindNativeInputActionForTag(InvalidTag, false);
	TestTrue(TEXT("Empty config must return null for native input lookup"),
		NativeResult == nullptr);

	const UInputAction* AbilityResult = InputConfig->FindAbilityInputActionForTag(InvalidTag, false);
	TestTrue(TEXT("Empty config must return null for ability input lookup"),
		AbilityResult == nullptr);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularInputConfigActionStructTest,
	"UEWorlds.ThirdParty.ModularGameplayData.InputConfig.ActionStructDefaults",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularInputConfigActionStructTest::RunTest(const FString& Parameters)
{
	FModularInputConfigAction ConfigAction;
	TestTrue(TEXT("Default InputAction must be null"), ConfigAction.InputAction == nullptr);
	TestFalse(TEXT("Default InputTag must be invalid"), ConfigAction.InputTag.IsValid());

	return true;
}

// ---------------------------------------------------------------------------
// Data Registration
// ---------------------------------------------------------------------------

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularInputConfigComponentCDOTest,
	"UEWorlds.ThirdParty.ModularGameplayData.Registration.InputConfigComponentCDO",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularInputConfigComponentCDOTest::RunTest(const FString& Parameters)
{
	const UClass* InputComponentClass = UModularInputConfigComponent::StaticClass();
	TestNotNull(TEXT("ModularInputConfigComponent StaticClass must exist"), InputComponentClass);
	TestTrue(TEXT("ModularInputConfigComponent must derive from UEnhancedInputComponent"),
		InputComponentClass->IsChildOf(UEnhancedInputComponent::StaticClass()));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularWorldActionBaseCDOTest,
	"UEWorlds.ThirdParty.ModularGameplayData.Registration.WorldActionBaseCDO",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularWorldActionBaseCDOTest::RunTest(const FString& Parameters)
{
	const UClass* WorldActionClass = UGameFeatureAction_ModularWorldBase::StaticClass();
	TestNotNull(TEXT("GameFeatureAction_ModularWorldBase StaticClass must exist"), WorldActionClass);
	TestTrue(TEXT("WorldActionBase must derive from UGameFeatureAction"),
		WorldActionClass->IsChildOf(UGameFeatureAction::StaticClass()));
	TestTrue(TEXT("WorldActionBase must be abstract"),
		WorldActionClass->HasAnyClassFlags(CLASS_Abstract));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FModularInputConfigEmptyArraysTest,
	"UEWorlds.ThirdParty.ModularGameplayData.Registration.EmptyInputArrays",
	EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModularInputConfigEmptyArraysTest::RunTest(const FString& Parameters)
{
	UModularInputConfig* InputConfig = NewObject<UModularInputConfig>();

	TestEqual(TEXT("NativeInputActions must be empty on creation"),
		InputConfig->NativeInputActions.Num(), 0);
	TestEqual(TEXT("AbilityInputActions must be empty on creation"),
		InputConfig->AbilityInputActions.Num(), 0);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
