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
}

void UItemSlot::RemoveItemFromSlot(int32 InIndex, EItemTypes ItemType)
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}
	FItemMaster EmptyItem;
	EmptyItem.DataTable.DataTable = nullptr;
	EmptyItem.Quantity = 0;

	switch (ItemType)
	{
	case EItemTypes::Armour_Equipment:
		EmptyItem.ItemType = EItemTypes::Armour_Equipment;
		PlayerInventory->GetArmour_EquipmentSlots()[InIndex] = EmptyItem;
		break;
	case EItemTypes::Consumeables:
		EmptyItem.ItemType = EItemTypes::Consumeables;
		PlayerInventory->GetConsumablesSlots()[InIndex] = EmptyItem;
		break;
	default:
		break;
	}
}

void UItemSlot::DropItemToSlot(FItemMaster InItem, int32 DraggedIndex, EItemTypes ItemType)
{	
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}

	// 드롭하는 슬롯이 비어있는 경우
	if (Item.Quantity == 0)
	{	
		switch (ItemType)
		{
		case EItemTypes::Armour_Equipment:
			PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = InItem;
			break;
		case EItemTypes::Consumeables:
			PlayerInventory->GetConsumablesSlots()[SlotIndex] = InItem;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (ItemType)
		{
		case EItemTypes::Armour_Equipment:
			PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = Item;
			PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = InItem;
			break;
		case EItemTypes::Consumeables:
			PlayerInventory->GetConsumablesSlots()[DraggedIndex] = Item;
			PlayerInventory->GetConsumablesSlots()[SlotIndex] = InItem;
			break;
		default:
			break;
		}		
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
		FString ContextString;
		FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			switch (RowData->EquipmentSlot)
			{
			case EEquipmentSlot::Sword:
				PlayerCharacter->SwapSword(RowData->Mesh);
				if (PlayerInventory->GetInventoryWidget()->GetSwordSlot()->GetItem().Quantity == 0)
				{
					PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = FItemMaster();
				}
				else
				{
					PlayerInventory->GetArmour_EquipmentSlots()[SlotIndex] = PlayerInventory->GetInventoryWidget()->GetSwordSlot()->GetItem();
				}
				PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
				PlayerInventory->GetInventoryWidget()->GetSwordSlot()->UpdateSlot(Item); 
				break;
			default:
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
