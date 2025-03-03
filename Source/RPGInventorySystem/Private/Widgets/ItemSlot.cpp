// Copyright by liclem97.


#include "Widgets/ItemSlot.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UItemSlot::NativePreConstruct()
{	
	Super::NativePreConstruct();

	if (Item.DataTable.DataTable == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: Item DataTable is nullptr."));
		return;
	}

	FString ContextString;
	FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
	if (RowData)
	{
		Image_Item->SetBrushFromTexture(RowData->Image);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("ItemSlot: Can't find RowData."));
		return;
	}
}

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Item->OnHovered.AddDynamic(this, &UItemSlot::OnItemButtonHovered);
	Button_Item->OnUnhovered.AddDynamic(this, &UItemSlot::OnItemButtonUnhovered);
}

void UItemSlot::OnItemButtonHovered()
{
	Border_Item->SetBrushColor(HoveredColor);
}

void UItemSlot::OnItemButtonUnhovered()
{
	Border_Item->SetBrushColor(UnhoveredColor);
}
