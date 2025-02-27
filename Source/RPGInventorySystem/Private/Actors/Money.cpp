// Copyright by liclem97.


#include "Actors/Money.h"

#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AMoney::AMoney()
{
	MoneyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Money"));
	MoneyMesh->SetSimulatePhysics(true);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(MoneyMesh);
	Widget->SetVisibility(false);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(MoneyMesh);
	Sphere->SetSphereRadius(64.f);
}

void AMoney::Interact_Implementation(UInventoryComponent* InventoryComp)
{
	if (!InventoryComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Money: Interact InventoryComp is nullptr."));
		return;
	}

	InventoryComp->SetMoney(InventoryComp->GetMoney() + Amount);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Money: %d"), InventoryComp->GetMoney()));
	Destroy();
}

void AMoney::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMoney::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMoney::OnEndOverlap);
}

void AMoney::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OverlayMaterial)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Money: OverlayMaterial is nullptr."));
		return;
	}
	MoneyMesh->SetOverlayMaterial(OverlayMaterial);
	Widget->SetVisibility(true);
}

void AMoney::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	MoneyMesh->SetOverlayMaterial(nullptr);
	Widget->SetVisibility(false);
}

