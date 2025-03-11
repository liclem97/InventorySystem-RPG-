// Copyright by liclem97.


#include "Widgets/LootBarSlot.h"

#include "Actors/Chest.h"
#include "Character/InventoryCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"
#include "Widgets/WeightWidget.h"

void ULootBarSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!Button_LootBar->OnClicked.IsAlreadyBound(this, &ULootBarSlot::OnLootBarButtonClicked))
	{
		Button_LootBar->OnClicked.AddDynamic(this, &ULootBarSlot::OnLootBarButtonClicked);
	}
}

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

void ULootBarSlot::OnLootBarButtonClicked()
{
	if (!PlayerInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("LootBarSlot: PlayerInventory is nullptr."));
		return;
	}

	if (!Chest)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("LootBarSlot: Chest is nullptr."));
		return;
	}

	if (PlayerInventory->AddItemToInventory(Item))
	{
		PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
		PlayerInventory->GetInventoryWidget()->GetWeightWidget()->UpdateWeight();
		Chest->RemoveItem(SlotIndex);
		RemoveFromParent();
	}
}
