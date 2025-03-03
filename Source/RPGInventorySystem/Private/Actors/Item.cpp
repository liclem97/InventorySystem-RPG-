// Copyright by liclem97.


#include "Actors/Item.h"


AItem::AItem()
{
	Mesh->SetCollisionProfileName("PhysicsActor");
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

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}
