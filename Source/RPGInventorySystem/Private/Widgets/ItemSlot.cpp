// Copyright by liclem97.


#include "Widgets/ItemSlot.h"

#include "Components/Border.h"
#include "Components/Button.h"

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
