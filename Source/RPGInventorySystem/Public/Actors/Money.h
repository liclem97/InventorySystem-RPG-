// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Money.generated.h"

class UWidgetComponent;
class USphereComponent;
class UInventoryComponent;

UCLASS()
class RPGINVENTORYSYSTEM_API AMoney : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AMoney();

	/** Interact Interface */
	virtual void Interact_Implementation(UInventoryComponent* InventoryComp) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MoneyMesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = Money)
	int32 Amount;

	UPROPERTY(EditAnywhere, Category = Material)
	UMaterial* OverlayMaterial;
};
