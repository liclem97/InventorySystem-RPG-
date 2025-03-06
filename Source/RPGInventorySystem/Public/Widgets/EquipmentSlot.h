// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "EquipmentSlot.generated.h"

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
class RPGINVENTORYSYSTEM_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateSlot(FItemMaster InItem);

	FORCEINLINE FItemMaster GetItem() const { return Item; }

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	void LoadEquipmentSlot();

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType, FItemStruct& RowData);

	UFUNCTION(BlueprintCallable)
	void DropItemToSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType);

	UFUNCTION()
	void OnItemButtonHovered();

	UFUNCTION()
	void OnItemButtonUnhovered();

	UFUNCTION()
	void OnItemButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Item;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Item;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_EquipmentSlot;

	FLinearColor HoveredColor = FColor::Orange;
	FLinearColor UnhoveredColor = FColor::White;

	UPROPERTY(EditAnywhere)
	EEquipmentSlot EquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FItemMaster Item;

	UPROPERTY(EditAnywhere)
	UTexture2D* HelmetImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* ArmourImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* PantsImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* BootsImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* SwordImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* ShieldImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* ConsumableImage;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 SlotIndex;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UInventoryComponent* PlayerInventory;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;
};
