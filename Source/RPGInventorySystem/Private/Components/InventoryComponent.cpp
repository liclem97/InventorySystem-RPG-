// Copyright by liclem97.


#include "Components/InventoryComponent.h"

#include "Character/InventoryCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveGame/InventorySaveGame.h"
#include "Widgets/InventoryFull.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"

UInventoryComponent::UInventoryComponent()
{
	EnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("EnhancedInputComponent"));

	MaxWeight = 400.f;
}

bool UInventoryComponent::AddItemToInventory(FItemMaster InItem)
{
	switch (InItem.ItemType)
	{
	case EItemTypes::Armour_Equipment:
		for (int32 i = 0; i < Armour_EquipmentSlots.Num(); i++)
		{
			if (Armour_EquipmentSlots[i].Quantity == 0)
			{
				Armour_EquipmentSlots[i] = InItem;
				return true; // 함수 종료
			}
		}
		// 슬롯이 모두 차있으면 false 반환
		return false;
	case EItemTypes::Consumeables:
		for (int32 i = 0; i < ConsumablesSlots.Num(); i++)
		{
			if (ConsumablesSlots[i].DataTable.RowName == InItem.DataTable.RowName)
			{
				FString ContextString;
				FItemStruct* RowData = InItem.DataTable.DataTable->FindRow<FItemStruct>(InItem.DataTable.RowName, ContextString);
				if (RowData)
				{
					if (RowData->StackSize >= ConsumablesSlots[i].Quantity + InItem.Quantity)
					{
						ConsumablesSlots[i].DataTable = InItem.DataTable;
						ConsumablesSlots[i].ItemType = InItem.ItemType;
						ConsumablesSlots[i].Quantity += InItem.Quantity;
						return true;
					}
				}
			}
		}
		for (int32 i = 0; i < ConsumablesSlots.Num(); i++)
		{
			if (ConsumablesSlots[i].Quantity == 0)
			{
				ConsumablesSlots[i] = InItem;
				return true; // 함수 종료
			}
		}
		return false;
	default:
		return false;
	}
}

void UInventoryComponent::InventoryFull()
{
	if (InventoryFullClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("InventoryComponent: InventoryFull class is nullptr."));
		return;
	}

	if (InventoryFullWidget)
	{
		InventoryFullWidget->AddToViewport();
		InventoryFullWidget->PlayAnimationFunc();
	}
	else
	{
		InventoryFullWidget = CreateWidget<UInventoryFull>(UGameplayStatics::GetPlayerController(this, 0), InventoryFullClass);
		InventoryFullWidget->AddToViewport();
	}
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeKeyBinding();
	InitializeWidgets();
	InitializeSlotSize();

	if (Armour_EquipmentSize <= 0 || ConsumablesSize <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("InventoryComponent: SlotSize is less than 0."));
	}

	if (IsValid(InventoryWidget))
	{
		InventoryWidget->GetItemInventory()->LoadInventory(this);
	}
}

void UInventoryComponent::InitializeKeyBinding()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InventoryMappingContext, 0);
		}
	}

	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UInventoryComponent::Interact);
	EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &UInventoryComponent::Inventory);
	EnhancedInputComponent->BindAction(SaveGameAction, ETriggerEvent::Started, this, &UInventoryComponent::SaveGame);
	EnhancedInputComponent->BindAction(DeleteSaveGameAction, ETriggerEvent::Started, this, &UInventoryComponent::DeleteSaveGame);
}

void UInventoryComponent::InitializeWidgets()
{
	if (!InventoryWidgetClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("InventoryComponent: InventoryWidgetClass is nullptr."));
		return;
	}

	InventoryWidget = CreateWidget<UInventoryWidget>(UGameplayStatics::GetPlayerController(this, 0), InventoryWidgetClass);
}

void UInventoryComponent::InitializeSlotSize()
{
	Armour_EquipmentSlots.SetNum(Armour_EquipmentSize);
	ConsumablesSlots.SetNum(ConsumablesSize);
}

void UInventoryComponent::Interact()
{	
	FVector Start = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation() - FVector(0, 0, 30.f);
	FVector End = Start;
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHit;
	if (UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		InteractRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true))
	{
		if (OutHit.GetActor() && OutHit.GetActor()->Implements<UInteractInterface>())
		{
			IInteractInterface::Execute_Interact(OutHit.GetActor(), this);
		}
	}	
}

void UInventoryComponent::Inventory()
{
	if (InventoryWidget)
	{
		if (!InventoryWidget->IsInViewport())
		{
			InventoryWidget->AddToViewport();

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());

			UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
			UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("InventoryComponent: InventoryWidget is nullptr."));
		return;
	}
}

void UInventoryComponent::SaveGame()
{	
	if (!InventorySaveGameClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("InventoryComponent: InventorySaveGameClass is nullptr."));
		return;
	}

	if (!UGameplayStatics::DoesSaveGameExist("InventorySaveGame", 0))
	{
		InventorySaveGame = Cast<UInventorySaveGame>(UGameplayStatics::CreateSaveGameObject(InventorySaveGameClass));
		InventorySaveGame->SetArmour_Equipment(Armour_EquipmentSlots);
		InventorySaveGame->SetConsumables(ConsumablesSlots);

		UGameplayStatics::SaveGameToSlot(InventorySaveGame, "InventorySaveGame", 0);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString("Save Game Complete."));
	}
}

void UInventoryComponent::DeleteSaveGame()
{
}
