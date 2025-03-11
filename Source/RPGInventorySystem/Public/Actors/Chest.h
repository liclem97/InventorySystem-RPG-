// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickup.h"
#include "Interface/InteractInterface.h"
#include "Chest.generated.h"

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API AChest : public APickup, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	AChest();

	/** Interact Interface */
	virtual void Interact_Implementation(UInventoryComponent* InventoryComp) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChestTop;
};
