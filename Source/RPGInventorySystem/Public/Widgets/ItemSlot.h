// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "ItemSlot.generated.h"

class UButton;
class UBorder;
class UImage;

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
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemButtonHovered();

	UFUNCTION()
	void OnItemButtonUnhovered();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Item;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Item;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Item;

	FLinearColor HoveredColor = FColor::Orange;
	FLinearColor UnhoveredColor = FColor::White;

	UPROPERTY(EditAnywhere)
	FItemMaster Item;

	int32 SlotIndex;
};
