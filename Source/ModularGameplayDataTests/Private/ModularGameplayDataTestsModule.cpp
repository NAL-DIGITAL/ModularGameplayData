#include "Modules/ModuleManager.h"

class FModularGameplayDataTestsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};

IMPLEMENT_MODULE(FModularGameplayDataTestsModule, ModularGameplayDataTests)
