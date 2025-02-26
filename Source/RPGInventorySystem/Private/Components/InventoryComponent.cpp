// Copyright by liclem97.


#include "Components/InventoryComponent.h"

#include "Character/InventoryCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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
	FVector Start = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation() - FVector(0, 0, 30.f);
	FVector End = Start;
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHit;
	if (UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		60.f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true))
	{
		if (OutHit.GetActor() && OutHit.GetActor()->Implements<UInteractInterface>())
		{
			IInteractInterface::Execute_Interact(OutHit.GetActor());
		}
	}	
}
