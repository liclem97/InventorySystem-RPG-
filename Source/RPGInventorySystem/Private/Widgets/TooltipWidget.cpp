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
			Text_Value->SetText(FText::AsNumber(RowData->Value * InItem.Quantity));
			Text_Weight->SetText(FText::AsNumber(RowData->Weight * InItem.Quantity));

			if (InItem.Quantity > 1)
			{
				Text_x->SetVisibility(ESlateVisibility::Visible);
				Text_Quantity->SetVisibility(ESlateVisibility::Visible);
				Text_Quantity->SetText(FText::AsNumber(InItem.Quantity));
			}
			else
			{
				Text_x->SetVisibility(ESlateVisibility::Hidden);
				Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("TooltipWidget: Can't find RowData."));
			return;
		}
	}	
}
