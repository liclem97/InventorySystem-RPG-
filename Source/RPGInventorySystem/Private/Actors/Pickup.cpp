// Copyright by liclem97.


#include "Actors/Pickup.h"

#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"

APickup::APickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Money"));
	Mesh->SetSimulatePhysics(true);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Mesh);
	Widget->SetVisibility(false);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
	Sphere->SetSphereRadius(64.f);

	static ConstructorHelpers::FObjectFinder<UMaterial> OverlayMaterialFinder(TEXT("/Game/Inventory/Materials/M_Outline.M_Outline"));
	if (OverlayMaterialFinder.Succeeded())
    {	
        OverlayMaterial = OverlayMaterialFinder.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find OverlayMaterial"));
    }

	static ConstructorHelpers::FClassFinder<UUserWidget> InteractWidgetFinder(TEXT("/Game/Inventory/Widget/WBP_Interact.WBP_Interact_C"));
	if (InteractWidgetFinder.Succeeded())
	{	
		Widget->SetWidgetClass(InteractWidgetFinder.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find InteractWidget"));
	}
}

void APickup::Interact_Implementation(UInventoryComponent* InventoryComp)
{
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APickup::OnEndOverlap);
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OverlayMaterial)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString("Pickup: OverlayMaterial is nullptr."));
		return;
	}
	Mesh->SetOverlayMaterial(OverlayMaterial);
	Widget->SetVisibility(true);
}

void APickup::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Mesh->SetOverlayMaterial(nullptr);
	Widget->SetVisibility(false);
}

