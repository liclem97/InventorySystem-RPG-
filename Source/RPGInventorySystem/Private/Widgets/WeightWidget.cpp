// Copyright by liclem97.


#include "Widgets/WeightWidget.h"

#include "Character/InventoryCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UWeightWidget::NativeConstruct()
{	
	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerCharacter->GetInventoryComponent_Implementation();
		UpdateWeight();
	}
}

void UWeightWidget::UpdateWeight()
{
	CurrentWeight = 0.f;
	FString ContextString;
	FItemMaster Item;
	FItemStruct* RowData;

	for (int32 i = 0; i < PlayerInventory->GetArmour_EquipmentSlots().Num(); i++)
	{	
		Item = PlayerInventory->GetArmour_EquipmentSlots()[i];
		if (Item.Quantity > 0)
		{
			RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
			if (RowData)
			{
				CurrentWeight += RowData->Weight;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("WeightWidget: Can't find RowData."));
				return;
			}
		}
	}	
	for (int32 i = 0; i < PlayerInventory->GetConsumablesSlots().Num(); i++)
	{
		Item = PlayerInventory->GetConsumablesSlots()[i];
		if (Item.Quantity > 0)
		{
			RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
			if (RowData)
			{
				CurrentWeight += (RowData->Weight * Item.Quantity);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("WeightWidget: Can't find RowData."));
				return;
			}
		}		
	}
	Text_CurrentWeight->SetText(FText::AsNumber(CurrentWeight));
	Text_MaxWeight->SetText(FText::AsNumber(PlayerInventory->GetMaxWeight()));
}
