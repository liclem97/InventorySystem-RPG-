// Copyright by liclem97.


#include "Widgets/DropWidget.h"

#include "Actors/Item.h"
#include "Character/InventoryCharacter.h"
#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/EquipmentSlot.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"
#include "Widgets/WeightWidget.h"

void UDropWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerInventory == nullptr ? PlayerCharacter->GetInventoryComponent_Implementation() : PlayerInventory;
	}
}

void UDropWidget::SpawnDropItem(FItemMaster InItem)
{	
	if (!PlayerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DropWidget: PlayerCharacter is nullptr."));
		return;
	}

	FTransform DropTransform = PlayerCharacter->GetDropPoint()->GetComponentTransform();

	SpawnedItem = Cast<AItem>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(),
		AItem::StaticClass(),
		DropTransform,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
	if (SpawnedItem)
	{
		SpawnedItem->SetItemData(InItem);

		UGameplayStatics::FinishSpawningActor(SpawnedItem, DropTransform);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DropWidget: Can't Spawn Drop Item."));
		return;
	}
}

void UDropWidget::DropItem(EItemTypes DraggedItemType, EItemDestination DraggedItemDestination, int32 DraggedIndex, FItemMaster InItem)
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DropWidget: PlayerInventory is nullptr."));
		return;
	}

	FString ContextString;
	FItemStruct* RowData;
	switch (DraggedItemType)
	{
	case EItemTypes::Armour_Equipment:
		if (DraggedItemDestination == EItemDestination::ItemSlot)
		{
			PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = FItemMaster();
			PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
		}
		else if (DraggedItemDestination == EItemDestination::EquipmentSlot)
		{
			RowData = InItem.DataTable.DataTable->FindRow<FItemStruct>(InItem.DataTable.RowName, ContextString);
			if (RowData)
			{
				switch (RowData->EquipmentSlot)
				{
				case EEquipmentSlot::Helmet:
					PlayerInventory->GetInventoryWidget()->GetHelmetSlot()->UpdateSlot(FItemMaster());
					break;
				case EEquipmentSlot::Chest:
					PlayerInventory->GetInventoryWidget()->GetArmourSlot()->UpdateSlot(FItemMaster());
					break;
				case EEquipmentSlot::Pants:
					PlayerInventory->GetInventoryWidget()->GetPantsSlot()->UpdateSlot(FItemMaster());
					break;
				case EEquipmentSlot::Boots:
					PlayerInventory->GetInventoryWidget()->GetBootsSlot()->UpdateSlot(FItemMaster());
					break;
				case EEquipmentSlot::Sword:
					PlayerInventory->GetInventoryWidget()->GetSwordSlot()->UpdateSlot(FItemMaster());
					break;
				case EEquipmentSlot::Shield:
					PlayerInventory->GetInventoryWidget()->GetShieldSlot()->UpdateSlot(FItemMaster());
					break;
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DropWidget: Can't find RowData."));
				return;
			}
		}
		break;
	case EItemTypes::Consumeables:
		if (DraggedItemDestination == EItemDestination::ItemSlot)
		{
			PlayerInventory->GetConsumablesSlots()[DraggedIndex] = FItemMaster();
			PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
		}
		else if (DraggedItemDestination == EItemDestination::EquipmentSlot)
		{
			RowData = InItem.DataTable.DataTable->FindRow<FItemStruct>(InItem.DataTable.RowName, ContextString);
			if (RowData)
			{
				switch (RowData->EquipmentSlot)
				{
				case EEquipmentSlot::Consumables:
					PlayerInventory->GetInventoryWidget()->GetConsumableSlot()->UpdateSlot(FItemMaster());
					break;
				default:
					break;
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DropWidget: Can't find RowData."));
				return;
			}
		}
		break;
	}
	SpawnDropItem(InItem);
	PlayerInventory->GetInventoryWidget()->GetWeightWidget()->UpdateWeight();
}
