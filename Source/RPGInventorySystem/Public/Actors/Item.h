// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Pickup.h"
#include "Item.generated.h"

struct FDataTableRowHandle;

UCLASS(BlueprintType, Blueprintable)
class RPGINVENTORYSYSTEM_API AItem : public APickup
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Data)
	FDataTableRowHandle ItemDataTableRow;
};
