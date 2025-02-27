// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoneyWidget.generated.h"

class AInventoryCharacter;
class UInventoryComponent;
class UTextBlock;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UMoneyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMoney();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_MoneyAmount;

	UPROPERTY()
	AInventoryCharacter* PlayerCharacter;

	UPROPERTY()
	UInventoryComponent* PlayerInventory;
};
