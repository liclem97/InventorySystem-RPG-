// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGInventorySystem.h"
#include "DraggedItem.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API UDraggedItem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FItemMaster Item;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Dragged;
};
