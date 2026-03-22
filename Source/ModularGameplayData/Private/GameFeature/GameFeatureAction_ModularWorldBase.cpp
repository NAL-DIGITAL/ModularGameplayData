// Copyright Chronicler.

#include "GameFeature/GameFeatureAction_ModularWorldBase.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureAction_ModularWorldBase)

void UGameFeatureAction_ModularWorldBase::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	GameInstanceStartHandles.FindOrAdd(Context) = FWorldDelegates::OnStartGameInstance.AddUObject(this, 
		&UGameFeatureAction_ModularWorldBase::HandleGameInstanceStart, FGameFeatureStateChangeContext(Context));

	// Add to any worlds with associated game instances that have already been initialized.
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			AddToWorld(WorldContext, Context);
		}
	}
}

void UGameFeatureAction_ModularWorldBase::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	if (const FDelegateHandle* FoundHandle = GameInstanceStartHandles.Find(Context);
		ensure(FoundHandle))
	{
		FWorldDelegates::OnStartGameInstance.Remove(*FoundHandle);
	}
	
}

void UGameFeatureAction_ModularWorldBase::HandleGameInstanceStart(UGameInstance* GameInstance, FGameFeatureStateChangeContext ChangeContext)
{
	if (const FWorldContext* WorldContext = GameInstance->GetWorldContext())
	{
		if (ChangeContext.ShouldApplyToWorldContext(*WorldContext))
		{
			AddToWorld(*WorldContext, ChangeContext);
		}
	}
}
