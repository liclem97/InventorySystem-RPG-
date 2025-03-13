// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "TooltipWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UTooltipWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateTooltip(FItemMaster InItem);

private:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Description;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Value;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_x;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Quantity;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Weight;
};
