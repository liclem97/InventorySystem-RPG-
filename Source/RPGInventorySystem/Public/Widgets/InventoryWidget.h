// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UItemInventory;
class UEquipmentSlot;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE UItemInventory* GetItemInventory() const { return ItemInventory; }
	FORCEINLINE UEquipmentSlot* GetHelmetSlot() const { return EquipmentSlot_Helmet; }
	FORCEINLINE UEquipmentSlot* GetArmourSlot() const { return EquipmentSlot_Armour; }
	FORCEINLINE UEquipmentSlot* GetPantsSlot() const { return EquipmentSlot_Pants; }
	FORCEINLINE UEquipmentSlot* GetBootsSlot() const { return EquipmentSlot_Boots; }
	FORCEINLINE UEquipmentSlot* GetSwordSlot() const { return EquipmentSlot_Sword; }
	FORCEINLINE UEquipmentSlot* GetShieldSlot() const { return EquipmentSlot_Shield; }

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

private:
	UPROPERTY(meta = (BindWidget))
	UItemInventory* ItemInventory;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* EquipmentSlot_Helmet;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* EquipmentSlot_Armour;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* EquipmentSlot_Pants;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* EquipmentSlot_Boots;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* EquipmentSlot_Sword;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* EquipmentSlot_Shield;
};
