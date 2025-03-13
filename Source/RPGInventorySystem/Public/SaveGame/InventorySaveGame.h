// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RPGInventorySystem.h"
#include "InventorySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UInventorySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	void SetArmour_Equipment(const TArray<FItemMaster>& InArmour_Equipment) { Armour_Equipment = InArmour_Equipment; }
	void SetConsumables(const TArray<FItemMaster>& InConsumables) { Consumables = InConsumables; }

private:
	TArray<FItemMaster> Armour_Equipment;
	TArray<FItemMaster> Consumables;
};
