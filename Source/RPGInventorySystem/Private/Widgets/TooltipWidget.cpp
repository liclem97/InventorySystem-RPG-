// Copyright by liclem97.


#include "Widgets/TooltipWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTooltipWidget::UpdateTooltip(FItemMaster InItem)
{	
	if (InItem.Quantity == 0)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		FString ContextString;
		FItemStruct* RowData = InItem.DataTable.DataTable->FindRow<FItemStruct>(InItem.DataTable.RowName, ContextString);
		if (RowData)
		{	
			Image_Item->SetBrushFromTexture(RowData->Image);
			Text_ItemName->SetText(RowData->Name);
			Text_Description->SetText(RowData->Description);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("TooltipWidget: Can't find RowData."));
			return;
		}
	}	
}
