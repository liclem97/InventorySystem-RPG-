// Copyright by liclem97.


#include "Widgets/ItemInventory.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UItemInventory::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Armour_Equipment->OnPressed.AddDynamic(this, &UItemInventory::OnArmourEquipmentButtonPressed);
	Button_Consumables->OnPressed.AddDynamic(this, &UItemInventory::OnConsumablesButtonPressed);
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
