// Copyright by liclem97.


#include "Actors/Chest.h"

AChest::AChest()
{
	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestTop"));
	ChestTop->SetupAttachment(Mesh);
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
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
