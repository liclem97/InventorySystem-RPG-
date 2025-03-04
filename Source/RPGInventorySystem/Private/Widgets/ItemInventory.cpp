// Copyright by liclem97.


#include "Widgets/ItemInventory.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "Widgets/ItemSlot.h"

void UItemInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!Button_Armour_Equipment->OnPressed.IsAlreadyBound(this, &UItemInventory::OnArmourEquipmentButtonPressed))
	{
		Button_Armour_Equipment->OnPressed.AddDynamic(this, &UItemInventory::OnArmourEquipmentButtonPressed);
	}
	if (!Button_Consumables->OnPressed.IsAlreadyBound(this, &UItemInventory::OnConsumablesButtonPressed))
	{
		Button_Consumables->OnPressed.AddDynamic(this, &UItemInventory::OnConsumablesButtonPressed);
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