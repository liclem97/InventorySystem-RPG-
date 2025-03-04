// Copyright by liclem97.


#include "Widgets/ItemSlot.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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
	
}

void UItemSlot::OnItemButtonHovered()
{
	Border_Item->SetBrushColor(HoveredColor);
}

void UItemSlot::OnItemButtonUnhovered()
{
	Border_Item->SetBrushColor(UnhoveredColor);
}
