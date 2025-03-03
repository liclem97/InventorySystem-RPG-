// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

class UButton;
class UBorder;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
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

	FLinearColor HoveredColor = FColor::Orange;
	FLinearColor UnhoveredColor = FColor::White;
};
