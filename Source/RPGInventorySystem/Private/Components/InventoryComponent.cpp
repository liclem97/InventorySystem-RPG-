// Copyright by liclem97.


#include "Components/InventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

UInventoryComponent::UInventoryComponent()
{
	EnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("EnhancedInputComponent"));
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InventoryMappingContext, 0);
		}
	}

	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UInventoryComponent::Interact);
}

void UInventoryComponent::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString("Interact"));
}
