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

void UItemInventory::SortByWeight()
{	
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item Inventory: PlayerInventory is nullptr."));
		return;
	}
	FString ContextString;
	FItemStruct* RowData;
	FItemMaster Item;
	float HighestWeight = 0.f;
	int32 HighestWeightIndex;

	WrapBox_Armour_Equipment->ClearChildren();
	WrapBox_Consumables->ClearChildren();

	TArray<FItemMaster>& SortedArmour_Equipment = PlayerInventory->GetArmour_EquipmentSlots();
	for (int32 i = 0; i < SortedArmour_Equipment.Num(); i++)
	{
		for (int32 j = i; j < SortedArmour_Equipment.Num(); j++)
		{	
			Item = SortedArmour_Equipment[j];
			RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
			if (RowData)
			{	
				if (RowData->Weight > HighestWeight)
				{
					HighestWeight = RowData->Weight;
					HighestWeightIndex = j;
				}	
//				SortedArmour_Equipment[j]
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemInventory: Can't find RowData."));
				return;
			}						
		}	
		Item = SortedArmour_Equipment[i];
		RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			if (HighestWeight > RowData->Weight)
			{
				SortedArmour_Equipment.Swap(HighestWeightIndex, i);
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
	for (int32 k = 0; k < SortedArmour_Equipment.Num(); k++)
	{
		ItemSlotWidget = CreateWidget<UItemSlot>(GetOwningPlayer(), ItemSlotClass);
		if (ItemSlotWidget)
		{
			ItemSlotWidget->SetItem(SortedArmour_Equipment[k]);
			ItemSlotWidget->SetSlotIndex(k);

			WrapBox_Armour_Equipment->AddChildToWrapBox(ItemSlotWidget);
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
	SortByWeight();
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