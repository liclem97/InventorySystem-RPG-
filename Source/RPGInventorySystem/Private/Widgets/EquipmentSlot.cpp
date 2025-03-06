// Copyright by liclem97.


#include "Widgets/EquipmentSlot.h"

#include "Character/InventoryCharacter.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"

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
	if (!Button_Item->OnClicked.IsAlreadyBound(this, &UEquipmentSlot::OnItemButtonClicked))
	{
		Button_Item->OnClicked.AddDynamic(this, &UEquipmentSlot::OnItemButtonClicked);
	}
}

void UEquipmentSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	LoadEquipmentSlot();
}

void UEquipmentSlot::NativeConstruct()
{	
	Super::NativeConstruct();

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerInventory == nullptr ? PlayerCharacter->GetInventoryComponent_Implementation() : PlayerInventory;
	}
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
	else
	{
		LoadEquipmentSlot();
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

void UEquipmentSlot::RemoveItemFromSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType)
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("EquipmentSlot: PlayerInventory is nullptr."));
		return;
	}

	if (DraggedItem.DataTable.DataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("EquipmentSlot: DraggedItem DataTable is nullptr."));
		return;
	}

	FString ContextString;
	FItemStruct* RowData = DraggedItem.DataTable.DataTable->FindRow<FItemStruct>(DraggedItem.DataTable.RowName, ContextString);
	if (RowData)
	{
		if (RowData->EquipmentSlot == EquipmentSlot)
		{
			PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = FItemMaster();
		}
	}
}

void UEquipmentSlot::DropItemToSlot(FItemMaster InItem, FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType)
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}

	// 장비가 이미 끼워져 있는 경우
	if (Item.Quantity != 0)
	{
		PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = Item;
	}
	UpdateSlot(DraggedItem);
	PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
}

void UEquipmentSlot::OnItemButtonHovered()
{
	Border_Item->SetBrushColor(HoveredColor);
}

void UEquipmentSlot::OnItemButtonUnhovered()
{
	Border_Item->SetBrushColor(UnhoveredColor);
}

void UEquipmentSlot::OnItemButtonClicked()
{	
	if (!IsValid(PlayerCharacter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("EquipmentSlot: PlayerCharacter is not valid."));
		return;
	}

	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("EquipmentSlot: PlayerInventory is nullptr."));
		return;
	}

	if (Item.Quantity != 0)
	{
		if (PlayerInventory->AddItemToInventory(Item))
		{
			Item = FItemMaster();
			UpdateSlot(Item);
			PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
		}
	}
}
