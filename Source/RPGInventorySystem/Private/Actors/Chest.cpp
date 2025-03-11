// Copyright by liclem97.


#include "Actors/Chest.h"

#include "Widgets/LootBarWidget.h"

AChest::AChest()
{
	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestTop"));
	ChestTop->SetupAttachment(Mesh);
}

void AChest::Interact_Implementation(UInventoryComponent* InventoryComp)
{	
	if (!LootBarWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Chest: LootBarWidget is nullptr."));
		return;
	}

	if (!LootBarWidget->IsVisible())
	{
		LootBarWidget->AddToViewport();
	}

	InteractChest();
}

void AChest::BeginPlay()
{
	Super::BeginPlay();

	if (LootBarWidgetClass)
	{
		LootBarWidget = CreateWidget<ULootBarWidget>(GetWorld(), LootBarWidgetClass);
		LootBarWidget->SetChest(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Chest: LootBarWidget class is nullptr."));
		return;
	}
}

void AChest::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ChestTop->SetOverlayMaterial(OverlayMaterial);
}

void AChest::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	ChestTop->SetOverlayMaterial(nullptr);
}

void AChest::RemoveItem(int32 InIndex)
{
	if (ItemsInChest[InIndex].Quantity > 0)
	{
		ItemsInChest[InIndex] = FItemMaster();
	}
}
