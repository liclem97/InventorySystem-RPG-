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
class UButton;

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
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void OnTakeItemsButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox_Chest;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_TakeItems;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

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
