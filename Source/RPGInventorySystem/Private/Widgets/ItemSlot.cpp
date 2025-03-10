// Copyright by liclem97.


#include "Widgets/ItemSlot.h"

#include "Character/InventoryCharacter.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/EquipmentSlot.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"
#include "Widgets/TooltipWidget.h"

void UItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!Button_Item->OnHovered.IsAlreadyBound(this, &UItemSlot::OnItemButtonHovered))
	{
		Button_Item->OnHovered.AddDynamic(this, &UItemSlot::OnItemButtonHovered);
	}
	if (!Button_Item->OnUnhovered.IsAlreadyBound(this, &UItemSlot::OnItemButtonUnhovered))
	{
		Button_Item->OnUnhovered.AddDynamic(this, &UItemSlot::OnItemButtonUnhovered);
	}
	if (!Button_Item->OnPressed.IsAlreadyBound(this, &UItemSlot::OnItemButtonPressed))
	{
		Button_Item->OnPressed.AddDynamic(this, &UItemSlot::OnItemButtonPressed);
	}
}

void UItemSlot::NativePreConstruct()
{	
	Super::NativePreConstruct();

	if (Item.Quantity == 0)
	{
		Image_Item->SetVisibility(ESlateVisibility::Hidden);
		Text_ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		if (Item.DataTable.DataTable == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: Item DataTable is nullptr."));
			return;
		}

		FString ContextString;
		FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			Image_Item->SetBrushFromTexture(RowData->Image);
			Image_Item->SetVisibility(ESlateVisibility::Visible);
			EquipmentSlot = RowData->EquipmentSlot;
			if (Item.Quantity > 1)
			{
				Text_ItemQuantity->SetVisibility(ESlateVisibility::Visible);
				Text_ItemQuantity->SetText(FText::AsNumber(Item.Quantity));
			}
			else
			{
				Text_ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: Can't find RowData."));
			return;
		}
	}	
}

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerInventory == nullptr ? PlayerCharacter->GetInventoryComponent_Implementation() : PlayerInventory;
	}
	if (ToolTipWidgetClass)
	{
		ItemTooltip = CreateWidget<UTooltipWidget>(this, ToolTipWidgetClass);
	}	
}

void UItemSlot::RemoveItemFromSlot(int32 DraggedIndex, EItemTypes DraggedItemType)
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}

	switch (DraggedItemType)
	{
	case EItemTypes::Armour_Equipment:
		PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = FItemMaster();
		break;
	case EItemTypes::Consumeables:
		PlayerInventory->GetConsumablesSlots()[DraggedIndex] = FItemMaster();
		break;
	default:
		break;
	}
}

void UItemSlot::DropItemToSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType, EItemDestination DraggedItemDestination)
{	
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}

	if (DraggedItem.DataTable.DataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: DraggedItem DataTable is nullptr."));
		return;
	}
	
	switch (DraggedItemType)
	{
	case EItemTypes::Armour_Equipment:
		if (DraggedItemDestination == EItemDestination::ItemSlot)
		{
			DropItemToItemSlot(DraggedItem, DraggedIndex, DraggedItemType);
		}
		else if (DraggedItemDestination == EItemDestination::EquipmentSlot)
		{	
			FString ContextString;
			FItemStruct* RowData = DraggedItem.DataTable.DataTable->FindRow<FItemStruct>(DraggedItem.DataTable.RowName, ContextString);
			if (RowData)
			{	
				if (Item.Quantity == 0 || EquipmentSlot == RowData->EquipmentSlot)
				{
					switch (RowData->EquipmentSlot)
					{
					case EEquipmentSlot::Helmet:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetHelmetSlot(), DraggedItem);
						break;
					case EEquipmentSlot::Chest:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetArmourSlot(), DraggedItem);
						break;
					case EEquipmentSlot::Pants:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetPantsSlot(), DraggedItem);
						break;
					case EEquipmentSlot::Boots:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetBootsSlot(), DraggedItem);
						break;
					case EEquipmentSlot::Sword:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetSwordSlot(), DraggedItem);
						break;
					case EEquipmentSlot::Shield:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetShieldSlot(), DraggedItem);
						break;
					}
				}				
			}
		}
		break;
	case EItemTypes::Consumeables:
		if (DraggedItemDestination == EItemDestination::ItemSlot)
		{
			DropItemToItemSlot(DraggedItem, DraggedIndex, DraggedItemType);
		}
		else if (DraggedItemDestination == EItemDestination::EquipmentSlot)
		{
			FString ContextString;
			FItemStruct* RowData = DraggedItem.DataTable.DataTable->FindRow<FItemStruct>(DraggedItem.DataTable.RowName, ContextString);
			if (RowData)
			{
				if (Item.Quantity == 0 || EquipmentSlot == RowData->EquipmentSlot)
				{
					switch (RowData->EquipmentSlot)
					{					
					case EEquipmentSlot::Consumables:
						DropItemToEquipmentSlot(*PlayerInventory->GetInventoryWidget()->GetConsumableSlot(), DraggedItem);
						break;
					}
				}
			}
		}
		break;
	}	
}

void UItemSlot::DropItemToItemSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType)
{
	RemoveItemFromSlot(DraggedIndex, DraggedItemType);
	if (Item.Quantity != 0)
	{	
		if (DraggedItemType == EItemTypes::Armour_Equipment)
		{
			PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = Item;
		}
		else if (DraggedItemType == EItemTypes::Consumeables)
		{
			PlayerInventory->GetConsumablesSlots()[DraggedIndex] = Item;
		}
	}
	if (DraggedItemType == EItemTypes::Armour_Equipment)
	{
		PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = DraggedItem;
	}
	else if (DraggedItemType == EItemTypes::Consumeables)
	{
		PlayerInventory->GetConsumablesSlots()[SlotIndex] = DraggedItem;
	}
	PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
}

void UItemSlot::DropItemToEquipmentSlot(UEquipmentSlot& InEquipmentSlot, FItemMaster DraggedItem)
{	
	if (DraggedItem.ItemType == EItemTypes::Armour_Equipment)
	{
		PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = DraggedItem;
	}
	else if (DraggedItem.ItemType == EItemTypes::Consumeables)
	{
		PlayerInventory->GetConsumablesSlots()[SlotIndex] = DraggedItem;
	}

	if (Item.Quantity != 0) // 드롭 슬롯이 비어있지 않은 경우.
	{
		InEquipmentSlot.UpdateSlot(Item);
	}
	else // 드롭 슬롯이 비어있는 경우.
	{
		InEquipmentSlot.UpdateSlot(FItemMaster());
	}	
	PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
}

void UItemSlot::OnItemButtonHovered()
{
	Border_Item->SetBrushColor(HoveredColor);
}

void UItemSlot::OnItemButtonUnhovered()
{
	Border_Item->SetBrushColor(UnhoveredColor);
}

void UItemSlot::OnItemButtonPressed()
{	
	if (!IsValid(Item.DataTable.DataTable))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: Item DataTable is nullptr."));
		return;
	}

	if (!IsValid(PlayerCharacter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerCharacter is not valid."));
		return;
	}

	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}

	if (Item.Quantity != 0)
	{	
		OnItemButtonUnhovered();
		FString ContextString;
		FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			switch (RowData->EquipmentSlot)
			{
			case EEquipmentSlot::Helmet:
				PlayerCharacter->SwapHelmet(RowData->Mesh);
				UpdateEquipment(*PlayerInventory->GetInventoryWidget()->GetHelmetSlot());
				break;
			case EEquipmentSlot::Chest:
				PlayerCharacter->SwapArmour(RowData->SkeletalMesh);
				UpdateEquipment(*PlayerInventory->GetInventoryWidget()->GetArmourSlot());
				break;
			case EEquipmentSlot::Pants:
				PlayerCharacter->SwapPants(RowData->SkeletalMesh);
				UpdateEquipment(*PlayerInventory->GetInventoryWidget()->GetPantsSlot());
				break;
			case EEquipmentSlot::Boots:
				PlayerCharacter->SwapBoots(RowData->SkeletalMesh);
				UpdateEquipment(*PlayerInventory->GetInventoryWidget()->GetBootsSlot());
				break;
			case EEquipmentSlot::Sword:
				PlayerCharacter->SwapSword(RowData->Mesh);
				UpdateEquipment(*PlayerInventory->GetInventoryWidget()->GetSwordSlot());
				break;
			case EEquipmentSlot::Shield:
				PlayerCharacter->SwapShield(RowData->Mesh);
				UpdateEquipment(*PlayerInventory->GetInventoryWidget()->GetShieldSlot());
				break;
			case EEquipmentSlot::Consumables:
				UpdateConsumables(*PlayerInventory->GetInventoryWidget()->GetConsumableSlot());
				break;
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: Can't find RowData."));
			return;
		}
	}
}

void UItemSlot::UpdateEquipment(UEquipmentSlot& InEquipmentSlot)
{
	if (InEquipmentSlot.GetItem().Quantity == 0)
	{
		PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = FItemMaster();
	}
	else
	{
		PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = InEquipmentSlot.GetItem();
	}
	PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
	InEquipmentSlot.UpdateSlot(Item);
}

void UItemSlot::UpdateConsumables(UEquipmentSlot& InEquipmentSlot)
{
	if (InEquipmentSlot.GetItem().Quantity == 0)
	{	
		FItemMaster EmptyItem;
		EmptyItem.ItemType = EItemTypes::Consumeables;
		PlayerInventory->GetConsumablesSlots()[SlotIndex] = EmptyItem;
	}
	else
	{
		PlayerInventory->GetConsumablesSlots()[SlotIndex] = InEquipmentSlot.GetItem();
	}
	PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
	InEquipmentSlot.UpdateSlot(Item);
}
