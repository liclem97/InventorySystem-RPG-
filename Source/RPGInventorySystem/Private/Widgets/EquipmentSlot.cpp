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
#include "Widgets/TooltipWidget.h"

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

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerInventory == nullptr ? PlayerCharacter->GetInventoryComponent_Implementation() : PlayerInventory;
	}	
}

void UEquipmentSlot::NativeConstruct()
{	
	Super::NativeConstruct();

	UpdateSlot(Item);
	if (ToolTipWidgetClass)
	{
		ItemTooltip = CreateWidget<UTooltipWidget>(this, ToolTipWidgetClass);
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
			switch (EquipmentSlot)
			{
			case EEquipmentSlot::Helmet:
				PlayerCharacter->SwapHelmet(RowData->Mesh);
				break;
			case EEquipmentSlot::Chest:
				PlayerCharacter->SwapArmour(RowData->SkeletalMesh);
				break;
			case EEquipmentSlot::Pants:
				PlayerCharacter->SwapPants(RowData->SkeletalMesh);
				break;
			case EEquipmentSlot::Boots:
				PlayerCharacter->SwapBoots(RowData->SkeletalMesh);
				break;
			case EEquipmentSlot::Sword:
				PlayerCharacter->SwapSword(RowData->Mesh);
				break;
			case EEquipmentSlot::Shield:
				PlayerCharacter->SwapShield(RowData->Mesh);
				break;
			case EEquipmentSlot::Consumables:
				Text_Quantity->SetVisibility(ESlateVisibility::Visible);
				Text_Quantity->SetText(FText::AsNumber(Item.Quantity));
				break;
			}
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
		switch (EquipmentSlot)
		{
		case EEquipmentSlot::Helmet:
			PlayerCharacter->SwapHelmet(PlayerCharacter->GetEmptyMesh());
			break;
		case EEquipmentSlot::Chest:
			PlayerCharacter->SwapArmour(PlayerCharacter->GetEmptySkeletalMesh());
			break;
		case EEquipmentSlot::Pants:
			PlayerCharacter->SwapPants(PlayerCharacter->GetEmptySkeletalMesh());
			break;
		case EEquipmentSlot::Boots:
			PlayerCharacter->SwapBoots(PlayerCharacter->GetEmptySkeletalMesh());
			break;
		case EEquipmentSlot::Sword:
			PlayerCharacter->SwapSword(PlayerCharacter->GetEmptyMesh());
			break;
		case EEquipmentSlot::Shield:
			PlayerCharacter->SwapShield(PlayerCharacter->GetEmptyMesh());
			break;
		case EEquipmentSlot::Consumables:
			Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
			Text_Quantity->SetText(FText::FromString(""));
			break;
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
		Image_Item->SetBrushFromTexture(ConsumableImage);
		Text_EquipmentSlot->SetText(FText::FromString("Potion"));
		break;
	}
}

void UEquipmentSlot::RemoveItemFromSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType, FItemStruct& RowData)
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

	if (RowData.EquipmentSlot == EquipmentSlot)
	{	
		if (DraggedItem.ItemType == EItemTypes::Armour_Equipment)
		{
			PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = FItemMaster();
		}
		else if (DraggedItem.ItemType == EItemTypes::Consumeables)
		{	
			FItemMaster EmptyItem;
			EmptyItem.ItemType = EItemTypes::Consumeables;
			PlayerInventory->GetConsumablesSlots()[DraggedIndex] = EmptyItem;
		}
	}
}

void UEquipmentSlot::DropItemToSlot(FItemMaster DraggedItem, int32 DraggedIndex, EItemTypes DraggedItemType)
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: PlayerInventory is nullptr."));
		return;
	}

	FString ContextString;
	FItemStruct* RowData = DraggedItem.DataTable.DataTable->FindRow<FItemStruct>(DraggedItem.DataTable.RowName, ContextString);
	if (RowData && RowData->EquipmentSlot == EquipmentSlot)
	{	
		// 슬롯에 있는 아이템과 드래그한 아이템이 다른 경우, 혹은 둘의 수량이 다른경우에만 아이템 드롭.
		if (!(Item.DataTable.RowName == DraggedItem.DataTable.RowName && Item.Quantity == DraggedItem.Quantity))
		{	
			RemoveItemFromSlot(DraggedItem, DraggedIndex, DraggedItemType, *RowData);
			if (DraggedItem.ItemType == EItemTypes::Armour_Equipment)
			{
				// 장비가 이미 끼워져 있는 경우
				if (Item.Quantity != 0)
				{
					PlayerInventory->GetArmour_EquipmentSlots()[DraggedIndex] = Item;
				}
			}
			else if (DraggedItem.ItemType == EItemTypes::Consumeables)
			{
				if (Item.Quantity != 0)
				{
					PlayerInventory->GetConsumablesSlots()[DraggedIndex] = Item;
				}				
			}			
			UpdateSlot(DraggedItem);
			PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
		}
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
