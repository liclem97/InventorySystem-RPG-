// Copyright by liclem97.


#include "Actors/Money.h"

#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AMoney::AMoney()
{
	Amount = 0;
}

void AMoney::Interact_Implementation(UInventoryComponent* InventoryComp)
{
	if (!InventoryComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Money: Interact InventoryComp is nullptr."));
		return;
	}

	InventoryComp->SetMoney(InventoryComp->GetMoney() + Amount);
	Destroy();
}

void AMoney::BeginPlay()
{
	Super::BeginPlay();
	
}
