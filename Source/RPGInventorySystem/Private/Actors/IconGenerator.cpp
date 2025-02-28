// Copyright by liclem97.


#include "Actors/IconGenerator.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"

AIconGenerator::AIconGenerator()
{
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AIconGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

