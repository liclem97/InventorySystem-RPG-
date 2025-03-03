// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInventory.generated.h"

class UButton;
class UBorder;
class UTextBlock;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UItemInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnArmourEquipmentButtonClicked();

	UFUNCTION()
	void OnConsumablesButtonClicked();

private:
	UPROPERTY(EditAnywhere, Category = Texture)
	UTexture2D* BorderTexture;

	UPROPERTY(EditAnywhere, Category = Texture)
	UTexture2D* BlankTexture;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Armour_Equipment;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Consumables;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Armour_Equipment;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Consumables;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_InventoryText;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher_Inventory;
};
