// Copyright by liclem97.


#include "Widgets/LootBarSlot.h"

#include "Actors/Chest.h"
#include "Character/InventoryCharacter.h"
#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULootBarSlot::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerCharacter->GetInventoryComponent_Implementation();
	}

	if (Item.Quantity == 0)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		if (Item.DataTable.DataTable == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("LootBarSlot: Item DataTable is nullptr."));
			return;
		}

		FString ContextString;
		FItemStruct* RowData = Item.DataTable.DataTable->FindRow<FItemStruct>(Item.DataTable.RowName, ContextString);
		if (RowData)
		{
			Image_Item->SetBrushFromTexture(RowData->Image);
			Text_ItemName->SetText(RowData->Name);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("LootBarSlot: Can't find RowData."));
			return;
		}
	}
}
