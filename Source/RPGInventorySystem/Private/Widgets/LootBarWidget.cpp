// Copyright by liclem97.


#include "Widgets/LootBarWidget.h"

#include "Actors/Chest.h"
#include "Character/InventoryCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/LootBarSlot.h"

void ULootBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerCharacter->GetInventoryComponent_Implementation();
	}

	WrapBox_Chest->ClearChildren();

	if (!Chest)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("LootBarWidget: Chest is nullptr"));
		return;
	}

	if (!LootBarSlotClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("LootBarWidget: LootBarSlotClass is nullptr"));
		return;
	}

	for (int32 i = 0; i < Chest->GetItemsInChest().Num(); i++)
	{	
		ULootBarSlot* NewLootBarSlot = CreateWidget<ULootBarSlot>(GetWorld(), LootBarSlotClass);
		NewLootBarSlot->SetItem(Chest->GetItemsInChest()[i]);
		NewLootBarSlot->SetChest(Chest);
		LootBarSlotWidget.Add(NewLootBarSlot);
		WrapBox_Chest->AddChildToWrapBox(NewLootBarSlot);
	}

}
