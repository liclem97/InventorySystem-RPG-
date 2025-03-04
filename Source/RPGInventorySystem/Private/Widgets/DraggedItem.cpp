// Copyright by liclem97.


#include "Widgets/DraggedItem.h"

#include "Components/Image.h"

void UDraggedItem::NativeConstruct()
{
	Super::NativeConstruct();

	if (Item.DataTable.DataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("DraggedItem: Item Datatable is nullptr."));
		return;
	}

	FString ContextString;
	FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
	if (RowData)
	{
		Image_Dragged->SetBrushFromTexture(RowData->Image);
	}
}
