#pragma once

#include "CoreMinimal.h"
#include "CavrnusSpatialConnector.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCavrnusCVTEditor, Log, All);

class FUICommandList;

class FCavrnusCVTEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void CreateCavrnusCvtRibbon(FMenuBarBuilder& Builder);

private:
	TSharedPtr<FUICommandList> PluginCommands;

	void RegisterMenus();
	void CreateRibbonSubEntry(FMenuBuilder& MenuBuilder);
	void TryAddSpatialConnector();
	void CavernizeCvtLevel();
	void ChangeLevelGameMode();
	void AddSpawnableItem(ACavrnusSpatialConnector& SC, const FString& Id, const FString& Path);
	UClass* GetDefaultBlueprint(const FString& Path, UClass* BaseClass);
};
