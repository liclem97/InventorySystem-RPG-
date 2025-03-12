// Copyright by liclem97.


#include "Widgets/ItemInventory.h"

#include "Character/InventoryCharacter.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/ItemSlot.h"

void UItemInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerCharacter->GetInventoryComponent_Implementation();
	}

	if (!Button_Armour_Equipment->OnPressed.IsAlreadyBound(this, &UItemInventory::OnArmourEquipmentButtonPressed))
	{
		Button_Armour_Equipment->OnPressed.AddDynamic(this, &UItemInventory::OnArmourEquipmentButtonPressed);
	}
	if (!Button_Consumables->OnPressed.IsAlreadyBound(this, &UItemInventory::OnConsumablesButtonPressed))
	{
		Button_Consumables->OnPressed.AddDynamic(this, &UItemInventory::OnConsumablesButtonPressed);
	}
	if (!Button_Weight->OnClicked.IsAlreadyBound(this, &UItemInventory::OnWeightButtonClicked))
	{
		Button_Weight->OnClicked.AddDynamic(this, &UItemInventory::OnWeightButtonClicked);
	}
	if (!Button_Value->OnClicked.IsAlreadyBound(this, &UItemInventory::OnValueButtonClicked))
	{
		Button_Value->OnClicked.AddDynamic(this, &UItemInventory::OnValueButtonClicked);
	}
}

void UItemInventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemSlotClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: ItemSlotClass is nullptr."));
		return;
	}
}

void UItemInventory::SortByWeight(TArray<FItemMaster>& SortedItemSlot, int32 InActivatedWidgetIndex)
{	
	FString ContextString;
	FItemStruct* RowData;
	FItemMaster Item;
	float HighestWeight = 0.f;
	int32 HighestWeightIndex = 0;

	if (InActivatedWidgetIndex == 0)
	{
		WrapBox_Armour_Equipment->ClearChildren();
	}
	else if (InActivatedWidgetIndex == 1)
	{
		WrapBox_Consumables->ClearChildren();
	}

	for (int32 i = 0; i < SortedItemSlot.Num(); i++)
	{
		for (int32 j = i; j < SortedItemSlot.Num(); j++)
		{
			Item = SortedItemSlot[j];
			RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
			if (RowData)
			{
				if ((RowData->Weight * Item.Quantity) > HighestWeight)
				{
					HighestWeight = (RowData->Weight * Item.Quantity);
					HighestWeightIndex = j;
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemInventory: Can't find RowData."));
				return;
			}
		}
		Item = SortedItemSlot[i];
		RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			if (HighestWeight > RowData->Weight)
			{
				SortedItemSlot.Swap(HighestWeightIndex, i);
			}
			HighestWeight = 0.f;
			HighestWeightIndex = 0;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemInventory: Can't find RowData."));
			return;
		}
	}
	for (int32 k = 0; k < SortedItemSlot.Num(); k++)
	{
		ItemSlotWidget = CreateWidget<UItemSlot>(GetOwningPlayer(), ItemSlotClass);
		if (ItemSlotWidget)
		{
			ItemSlotWidget->SetItem(SortedItemSlot[k]);
			ItemSlotWidget->SetSlotIndex(k);

			if (InActivatedWidgetIndex == 0)
			{
				WrapBox_Armour_Equipment->AddChildToWrapBox(ItemSlotWidget);
			}
			else if (InActivatedWidgetIndex == 1)
			{
				WrapBox_Consumables->AddChildToWrapBox(ItemSlotWidget);
			}
		}
	}
}

void UItemInventory::SortByValue(TArray<FItemMaster>& SortedItemSlot, int32 InActivatedWidgetIndex)
{
	FString ContextString;
	FItemStruct* RowData;
	FItemMaster Item;
	float HighestValue = 0.f;
	int32 HighestValueIndex = 0;

	if (InActivatedWidgetIndex == 0)
	{
		WrapBox_Armour_Equipment->ClearChildren();
	}
	else if (InActivatedWidgetIndex == 1)
	{
		WrapBox_Consumables->ClearChildren();
	}

	for (int32 i = 0; i < SortedItemSlot.Num(); i++)
	{
		for (int32 j = i; j < SortedItemSlot.Num(); j++)
		{
			Item = SortedItemSlot[j];
			RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
			if (RowData)
			{
				if ((RowData->Value * Item.Quantity) > HighestValue)
				{
					HighestValue = (RowData->Value * Item.Quantity);
					HighestValueIndex = j;
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemInventory: Can't find RowData."));
				return;
			}
		}
		Item = SortedItemSlot[i];
		RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			if (HighestValue > RowData->Value)
			{
				SortedItemSlot.Swap(HighestValueIndex, i);
			}
			HighestValue = 0.f;
			HighestValueIndex = 0;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemInventory: Can't find RowData."));
			return;
		}
	}
	for (int32 k = 0; k < SortedItemSlot.Num(); k++)
	{
		ItemSlotWidget = CreateWidget<UItemSlot>(GetOwningPlayer(), ItemSlotClass);
		if (ItemSlotWidget)
		{
			ItemSlotWidget->SetItem(SortedItemSlot[k]);
			ItemSlotWidget->SetSlotIndex(k);

			if (InActivatedWidgetIndex == 0)
			{
				WrapBox_Armour_Equipment->AddChildToWrapBox(ItemSlotWidget);
			}
			else if (InActivatedWidgetIndex == 1)
			{
				WrapBox_Consumables->AddChildToWrapBox(ItemSlotWidget);
			}
		}
	}
}

void UItemInventory::OnArmourEquipmentButtonPressed()
{	
	if (BorderTexture == nullptr || BlankTexture == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: Texture is nullptr."));
		return;
	}
	Border_Armour_Equipment->SetBrushFromTexture(BorderTexture);
	Border_Consumables->SetBrushFromTexture(BlankTexture);
	Text_InventoryText->SetText(FText::FromString("Armour & Equipment"));
	WidgetSwitcher_Inventory->SetActiveWidgetIndex(0);
}

void UItemInventory::OnConsumablesButtonPressed()
{
	if (BorderTexture == nullptr || BlankTexture == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: Texture is nullptr."));
		return;
	}
	Border_Armour_Equipment->SetBrushFromTexture(BlankTexture);
	Border_Consumables->SetBrushFromTexture(BorderTexture);
	Text_InventoryText->SetText(FText::FromString("Consumables"));
	WidgetSwitcher_Inventory->SetActiveWidgetIndex(1);
}

void UItemInventory::OnWeightButtonClicked()
{	
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: PlayerInventory is nullptr."));
		return;
	}

	switch (WidgetSwitcher_Inventory->GetActiveWidgetIndex())
	{
	case 0: // Equipment Tab
		SortByWeight(PlayerInventory->GetArmour_EquipmentSlots(), WidgetSwitcher_Inventory->GetActiveWidgetIndex());
		break;
	case 1: // Consumables Tab
		SortByWeight(PlayerInventory->GetConsumablesSlots(), WidgetSwitcher_Inventory->GetActiveWidgetIndex());
		break;
	default:
		break;
	}	
}

void UItemInventory::OnValueButtonClicked()
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: PlayerInventory is nullptr."));
		return;
	}

	switch (WidgetSwitcher_Inventory->GetActiveWidgetIndex())
	{
	case 0: // Equipment Tab
		SortByValue(PlayerInventory->GetArmour_EquipmentSlots(), WidgetSwitcher_Inventory->GetActiveWidgetIndex());
		break;
	case 1: // Consumables Tab
		SortByValue(PlayerInventory->GetConsumablesSlots(), WidgetSwitcher_Inventory->GetActiveWidgetIndex());
		break;
	default:
		break;
	}
}

void UItemInventory::LoadInventory(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: InInventoryComponent is nullptr."));
		return;
	}

	WrapBox_Armour_Equipment->ClearChildren();
	WrapBox_Consumables->ClearChildren();

	for (int32 i = 0; i < InInventoryComponent->GetArmour_EquipmentSlots().Num(); i++)
	{
		ItemSlotWidget = CreateWidget<UItemSlot>(GetOwningPlayer(), ItemSlotClass);
		if (ItemSlotWidget)
		{
			ItemSlotWidget->SetItem(InInventoryComponent->GetArmour_EquipmentSlots()[i]);
			ItemSlotWidget->SetSlotIndex(i);

			WrapBox_Armour_Equipment->AddChildToWrapBox(ItemSlotWidget);
		}
	}

	for (int32 i = 0; i < InInventoryComponent->GetConsumablesSlots().Num(); i++)
	{
		ItemSlotWidget = CreateWidget<UItemSlot>(GetOwningPlayer(), ItemSlotClass);
		if (ItemSlotWidget)
		{
			ItemSlotWidget->SetItem(InInventoryComponent->GetConsumablesSlots()[i]);
			ItemSlotWidget->SetSlotIndex(i);

			WrapBox_Consumables->AddChildToWrapBox(ItemSlotWidget);
		}
	}
}