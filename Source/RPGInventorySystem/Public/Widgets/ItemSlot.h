// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "ItemSlot.generated.h"

class UButton;
class UBorder;
class UImage;
class UTextBlock;
class UInventoryComponent;
class AInventoryCharacter;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Setter */
	FORCEINLINE void SetItem(FItemMaster InItem) { Item = InItem; }
	FORCEINLINE void SetSlotIndex(int32 InSlotIndex) { SlotIndex = InSlotIndex; }
	/** End Setter */

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromSlot(int32 InIndex, EItemTypes ItemType);

	UFUNCTION(BlueprintCallable)
	void DropItemToSlot(FItemMaster InItem, int32 DraggedIndex, EItemTypes ItemType);

	UFUNCTION()
	void OnItemButtonHovered();

	UFUNCTION()
	void OnItemButtonUnhovered();

	UFUNCTION()
	void OnItemButtonPressed();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Item;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Item;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ItemQuantity;

	FLinearColor HoveredColor = FColor::Orange;
	FLinearColor UnhoveredColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FItemMaster Item;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 SlotIndex;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UInventoryComponent* PlayerInventory;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;
};
