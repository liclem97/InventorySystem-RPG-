// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryFull.generated.h"

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UInventoryFull : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimationFunc();

protected:
	virtual void NativeConstruct() override;
};
