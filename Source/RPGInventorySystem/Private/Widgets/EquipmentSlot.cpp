// Copyright by liclem97.


#include "Widgets/EquipmentSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"

void UEquipmentSlot::NativeOnInitialized()
{
	if (!Button_Item->OnHovered.IsAlreadyBound(this, &UEquipmentSlot::OnItemButtonHovered))
	{
		Button_Item->OnHovered.AddDynamic(this, &UEquipmentSlot::OnItemButtonHovered);
	}
	if (!Button_Item->OnUnhovered.IsAlreadyBound(this, &UEquipmentSlot::OnItemButtonUnhovered))
	{
		Button_Item->OnUnhovered.AddDynamic(this, &UEquipmentSlot::OnItemButtonUnhovered);
	}
}

void UEquipmentSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	LoadEquipmentSlot();
}

void UEquipmentSlot::UpdateSlot(FItemMaster InItem)
{
	Item = InItem;
	if (Item.Quantity != 0)
	{
		FString ContextString;
		FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			Image_Item->SetBrushFromTexture(RowData->Image);
			Image_Item->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("EquipmentSlot: Can't find RowData."));
			return;
		}
	}
}

void UEquipmentSlot::LoadEquipmentSlot()
{
	switch (EquipmentSlot)
	{
	case EEquipmentSlot::Helmet:
		Image_Item->SetBrushFromTexture(HelmetImage);
		Text_EquipmentSlot->SetText(FText::FromString("Helmet"));
		break;
	case EEquipmentSlot::Chest:
		Image_Item->SetBrushFromTexture(ArmourImage);
		Text_EquipmentSlot->SetText(FText::FromString("Armour"));
		break;
	case EEquipmentSlot::Pants:
		Image_Item->SetBrushFromTexture(PantsImage);
		Text_EquipmentSlot->SetText(FText::FromString("Pants"));
		break;
	case EEquipmentSlot::Boots:
		Image_Item->SetBrushFromTexture(BootsImage);
		Text_EquipmentSlot->SetText(FText::FromString("Boots"));
		break;
	case EEquipmentSlot::Sword:
		Image_Item->SetBrushFromTexture(SwordImage);
		Text_EquipmentSlot->SetText(FText::FromString("Sword"));
		break;
	case EEquipmentSlot::Shield:
		Image_Item->SetBrushFromTexture(ShieldImage);
		Text_EquipmentSlot->SetText(FText::FromString("Shield"));
		break;
	case EEquipmentSlot::Consumables:
		break;
	}
}

void UEquipmentSlot::OnItemButtonHovered()
{
	Border_Item->SetBrushColor(HoveredColor);
}

void UEquipmentSlot::OnItemButtonUnhovered()
{
	Border_Item->SetBrushColor(UnhoveredColor);
}
