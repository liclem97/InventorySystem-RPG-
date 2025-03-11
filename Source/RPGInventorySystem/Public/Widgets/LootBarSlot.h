// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "LootBarSlot.generated.h"

class AChest;
class UImage;
class UTextBlock;
class UInventoryComponent;
class AInventoryCharacter;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API ULootBarSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetItem(FItemMaster InItem) { Item = InItem; }
	FORCEINLINE void SetChest(AChest* InChest) { Chest = InChest; }

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ItemName;

	FItemMaster Item;

	UPROPERTY()
	AChest* Chest;

	UPROPERTY()
	UInventoryComponent* PlayerInventory;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;
};
