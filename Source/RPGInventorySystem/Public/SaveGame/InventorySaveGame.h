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
	void SetArmour_Equipment(TArray<FItemMaster>& InArmour_Equipment) { Armour_Equipment = InArmour_Equipment; }
	void SetConsumables(TArray<FItemMaster>& InConsumables) { Consumables = InConsumables; }

	const TArray<FItemMaster>& GetArmour_Equipment() const { return Armour_Equipment; }
	const TArray<FItemMaster>& GetConsumables() const { return Consumables; }


private:
	UPROPERTY()
	TArray<FItemMaster> Armour_Equipment;

	UPROPERTY()
	TArray<FItemMaster> Consumables;
};
