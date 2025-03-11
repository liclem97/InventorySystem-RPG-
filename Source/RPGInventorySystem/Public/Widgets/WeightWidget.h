// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "WeightWidget.generated.h"

class AInventoryCharacter;
class UInventoryComponent;
class UTextBlock;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UWeightWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWeight();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentWeight;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaxWeight;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;

	UPROPERTY()
	UInventoryComponent* PlayerInventory;
	
	float CurrentWeight;
};
