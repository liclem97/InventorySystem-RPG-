// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Pickup.generated.h"

class UWidgetComponent;
class USphereComponent;
class UInventoryComponent;

UCLASS()
class RPGINVENTORYSYSTEM_API APickup : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	APickup();

	/** Interact Interface */
	virtual void Interact_Implementation(UInventoryComponent* InventoryComp) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = Material)
	UMaterial* OverlayMaterial;
};
