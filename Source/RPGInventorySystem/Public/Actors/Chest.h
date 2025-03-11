// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickup.h"
#include "Chest.generated.h"

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API AChest : public APickup
{
	GENERATED_BODY()
	
public:
	AChest();

protected:
	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


private:
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* ChestTop;
};
