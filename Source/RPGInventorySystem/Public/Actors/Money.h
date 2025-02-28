// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Pickup.h"
#include "Interface/InteractInterface.h"
#include "Money.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGINVENTORYSYSTEM_API AMoney : public APickup
{
	GENERATED_BODY()
	
public:	
	AMoney();

	/** Interact Interface */
	virtual void Interact_Implementation(UInventoryComponent* InventoryComp) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Money)
	int32 Amount;
};
