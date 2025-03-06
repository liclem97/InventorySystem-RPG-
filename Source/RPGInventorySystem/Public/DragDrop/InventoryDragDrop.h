// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "RPGInventorySystem.h"
#include "InventoryDragDrop.generated.h"

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UInventoryDragDrop : public UDragDropOperation
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 Index;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FItemMaster Item;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EItemDestination ItemDestination;
};
