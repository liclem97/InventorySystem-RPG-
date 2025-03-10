// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "DropWidget.generated.h"

class UInventoryDragDrop;
class UInventoryComponent;
class AInventoryCharacter;
class AItem;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UDropWidget : public UUserWidget
{
	GENERATED_BODY()	

protected:
	virtual void NativeConstruct() override;

	void SpawnDropItem(FItemMaster InItem);

	UFUNCTION(BlueprintCallable)
	void DropItem(EItemTypes DraggedItemType, EItemDestination DraggedItemDestination, int32 DraggedIndex, FItemMaster InItem);

	UPROPERTY(BlueprintReadWrite)
	UInventoryDragDrop* InventoryDragDrop;

private:
	UPROPERTY()
	UInventoryComponent* PlayerInventory;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;

	UPROPERTY()
	AItem* SpawnedItem;
};
