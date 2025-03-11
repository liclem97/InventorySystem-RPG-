// Copyright by liclem97.


#include "Widgets/LootBarWidget.h"

#include "Actors/Chest.h"
#include "Character/InventoryCharacter.h"
#include "Components/Button.h"
#include "Components/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/LootBarSlot.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"

void ULootBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!Button_Close->OnClicked.IsAlreadyBound(this, &ULootBarWidget::OnCloseButtonClicked))
	{
		Button_Close->OnClicked.AddDynamic(this, &ULootBarWidget::OnCloseButtonClicked);
	}
	if (!Button_TakeItems->OnClicked.IsAlreadyBound(this, &ULootBarWidget::OnTakeItemsButtonClicked))
	{
		Button_TakeItems->OnClicked.AddDynamic(this, &ULootBarWidget::OnTakeItemsButtonClicked);
	}
}

void ULootBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

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

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());

	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);

	for (int32 i = 0; i < Chest->GetItemsInChest().Num(); i++)
	{	
		ULootBarSlot* NewLootBarSlot = CreateWidget<ULootBarSlot>(GetWorld(), LootBarSlotClass);
		NewLootBarSlot->SetItem(Chest->GetItemsInChest()[i]);
		NewLootBarSlot->SetChest(Chest);
		NewLootBarSlot->SetSlotIndex(i);

		LootBarSlotWidget.Add(NewLootBarSlot);
		WrapBox_Chest->AddChildToWrapBox(NewLootBarSlot);
	}
}

void ULootBarWidget::OnCloseButtonClicked()
{	
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeGameOnly());

	RemoveFromParent();
	Chest->CloseChest();
}

void ULootBarWidget::OnTakeItemsButtonClicked()
{	
	for (int32 i = 0; i < Chest->GetItemsInChest().Num(); i++)
	{
		if (PlayerInventory->AddItemToInventory(Chest->GetItemsInChest()[i]))
		{
			PlayerInventory->GetInventoryWidget()->GetItemInventory()->LoadInventory(PlayerInventory);
			Chest->RemoveItem(i);
			LootBarSlotWidget[i]->RemoveFromParent();
		}
	}	
}
