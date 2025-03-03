// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UItemInventory;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE UItemInventory* GetItemInventory() const { return ItemInventory; }

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

private:
	UPROPERTY(meta = (BindWidget))
	UItemInventory* ItemInventory;
};
