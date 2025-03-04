// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGInventorySystem.h"
#include "InventoryComponent.generated.h"

class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
class UInventoryWidget;
class UInventoryFull;
	
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGINVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	bool AddItemToInventory(FItemMaster InItem);
	void InventoryFull();

	/** Getter */
	FORCEINLINE int32 GetMoney() const { return Money; }
	FORCEINLINE const TArray<FItemMaster>& GetArmour_EquipmentSlots() const { return Armour_EquipmentSlots; }
	FORCEINLINE const TArray<FItemMaster>& GetConsumablesSlots() const { return ConsumablesSlots; }
	FORCEINLINE UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }
	/** End Getter */

	/** Setter */
	FORCEINLINE void SetMoney(int32 InMoney) { Money = InMoney; }
	/** End Setter */
protected:
	virtual void BeginPlay() override;
	void InitializeKeyBinding();
	void InitializeWidgets();
	void InitializeSlotSize();
	void Interact();
	void Inventory();

private:
	/** Enhanced Input Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UEnhancedInputComponent* EnhancedInputComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InventoryMappingContext;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere)
	float InteractRadius = 120.f;

	int32 Money;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UInventoryWidget* InventoryWidget;

	TArray<FItemMaster> Armour_EquipmentSlots;

	TArray<FItemMaster> ConsumablesSlots;

	UPROPERTY(EditAnywhere, Category = ItemSlot)
	int32 Armour_EquipmentSize;

	UPROPERTY(EditAnywhere, Category = ItemSlot)
	int32 ConsumablesSize;

	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<UInventoryFull> InventoryFullClass;

	UInventoryFull* InventoryFullWidget;
};
