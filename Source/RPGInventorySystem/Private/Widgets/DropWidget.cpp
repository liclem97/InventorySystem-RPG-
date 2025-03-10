// Copyright by liclem97.


#include "Widgets/DropWidget.h"

#include "Actors/Item.h"
#include "Character/InventoryCharacter.h"
#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"

void UDropWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerInventory == nullptr ? PlayerCharacter->GetInventoryComponent_Implementation() : PlayerInventory;
	}
}

void UDropWidget::DropItem(EItemTypes DraggedItemType, EItemDestination DraggedItemDestination, int32 DraggedIndex, FItemMaster InItem)
{	
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DropWidget: PlayerInventory is nullptr."));
		return;
	}

	FTransform DropTransform = PlayerCharacter->GetDropPoint()->GetComponentTransform();

	switch (DraggedItemType)
	{
	case EItemTypes::Armour_Equipment:
		if (DraggedItemDestination == EItemDestination::ItemSlot)
		{
			PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = FItemMaster();
			PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
		
			SpawnedItem = Cast<AItem>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(),
													AItem::StaticClass(),
													DropTransform,
													ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
			if (SpawnedItem)
			{
				SpawnedItem->SetItemData(InItem);

				UGameplayStatics::FinishSpawningActor(SpawnedItem, DropTransform);
			}
		}
		else if (DraggedItemDestination == EItemDestination::EquipmentSlot)
		{

		}
		break;
	case EItemTypes::Consumeables:
		if (DraggedItemDestination == EItemDestination::ItemSlot)
		{

		}
		else if (DraggedItemDestination == EItemDestination::EquipmentSlot)
		{

		}
		break;
	}
}
