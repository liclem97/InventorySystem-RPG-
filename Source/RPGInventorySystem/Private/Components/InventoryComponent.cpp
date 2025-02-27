// Copyright by liclem97.


#include "Components/InventoryComponent.h"

#include "Character/InventoryCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/InventoryWidget.h"

UInventoryComponent::UInventoryComponent()
{
	EnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("EnhancedInputComponent"));
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeKeyBinding();
	InitializeWidgets();
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
		if (InventoryWidget->IsVisible())
		{
			InventoryWidget->RemoveFromParent();
		}
		else
		{	
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());

			UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
			UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
			InventoryWidget->AddToViewport();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("InventoryComponent: InventoryWidget is nullptr."));
		return;
	}
}
