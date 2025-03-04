// Copyright by liclem97.


#include "Widgets/ItemSlot.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemSlot::NativePreConstruct()
{	
	Super::NativePreConstruct();

	if (Item.Quantity == 0)
	{
		Image_Item->SetVisibility(ESlateVisibility::Hidden);
		Text_ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
	}
	
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
		Image_Item->SetVisibility(ESlateVisibility::Visible);
		Text_ItemQuantity->SetVisibility(ESlateVisibility::Visible);
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

	// 델리게이트에 함수가 이미 바인딩되어 있는지 확인
	if (!Button_Item->OnHovered.IsBound())
	{
		Button_Item->OnHovered.AddDynamic(this, &UItemSlot::OnItemButtonHovered);
	}
	if (!Button_Item->OnUnhovered.IsBound())
	{
		Button_Item->OnUnhovered.AddDynamic(this, &UItemSlot::OnItemButtonUnhovered);
	}
}

void UItemSlot::OnItemButtonHovered()
{
	Border_Item->SetBrushColor(HoveredColor);
}

void UItemSlot::OnItemButtonUnhovered()
{
	Border_Item->SetBrushColor(UnhoveredColor);
}
