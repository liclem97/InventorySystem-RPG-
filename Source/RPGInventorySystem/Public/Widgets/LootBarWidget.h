// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootBarWidget.generated.h"

class AChest;
class UInventoryComponent;
class AInventoryCharacter;
class UWrapBox;
class ULootBarSlot;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API ULootBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetChest(AChest* InChest) { Chest = InChest; }

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox_Chest;

	UPROPERTY()
	AChest* Chest;

	UPROPERTY()
	UInventoryComponent* PlayerInventory;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LootBarSlotClass;

	TArray<ULootBarSlot*> LootBarSlotWidget;
};
