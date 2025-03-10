// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGInventorySystem.h"
#include "Interface/InteractInterface.h"
#include "Actors/Pickup.h"
#include "Item.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGINVENTORYSYSTEM_API AItem : public APickup, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void OnConstruction(const FTransform& Transform) override;

	/** Interact Interface */
	virtual void Interact_Implementation(UInventoryComponent* InventoryComp) override;

	FORCEINLINE void SetItemData(FItemMaster InItemData) { ItemData = InItemData; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Data)
	FItemMaster ItemData;
};
