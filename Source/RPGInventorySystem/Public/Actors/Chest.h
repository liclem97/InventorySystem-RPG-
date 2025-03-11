// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickup.h"
#include "Interface/InteractInterface.h"
#include "RPGInventorySystem.h"
#include "Chest.generated.h"

class ULootBarWidget;

/**
 * 
 */
UCLASS()
class RPGINVENTORYSYSTEM_API AChest : public APickup, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	AChest();
	void RemoveItem(int32 InIndex);

	/** Interact Interface */
	virtual void Interact_Implementation(UInventoryComponent* InventoryComp) override;

	UFUNCTION(BlueprintImplementableEvent)
	void CloseChest();

	FORCEINLINE TArray<FItemMaster>& GetItemsInChest() { return ItemsInChest; }

protected:
	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintImplementableEvent)
	void InteractChest();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChestTop;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LootBarWidgetClass;

	UPROPERTY()
	ULootBarWidget* LootBarWidget;

	UPROPERTY(EditAnywhere)
	TArray<FItemMaster> ItemsInChest;
};
