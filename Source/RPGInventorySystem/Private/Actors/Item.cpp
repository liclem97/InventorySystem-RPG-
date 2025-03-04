// Copyright by liclem97.


#include "Actors/Item.h"

#include "Components/InventoryComponent.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/ItemInventory.h"

AItem::AItem()
{
	Mesh->SetCollisionProfileName("PhysicsActor");

	ItemData.Quantity = 1;
}

void AItem::OnConstruction(const FTransform& Transform)
{	
	
	if (!IsValid(ItemData.DataTable.DataTable))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item: Item DataTable is nullptr."));
		return;
	}

	FString ContextString;
	FItemStruct* RowData = ItemData.DataTable.DataTable->FindRow<FItemStruct>(ItemData.DataTable.RowName, ContextString);
	if (RowData)
	{
		Mesh->SetStaticMesh(RowData->Mesh);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item: Can't find RowData."));
		return;
	}
}

void AItem::Interact_Implementation(UInventoryComponent* InventoryComp)
{	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Item: Interact"));

	if (InventoryComp == nullptr) return;

	if (InventoryComp->AddItemToInventory(ItemData))
	{
		InventoryComp->GetInventoryWidget()->GetItemInventory()->LoadInventory(InventoryComp);
		Destroy();
	}
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}
