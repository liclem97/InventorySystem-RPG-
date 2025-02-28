// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IconGenerator.generated.h"

class USceneCaptureComponent2D;

UCLASS()
class RPGINVENTORYSYSTEM_API AIconGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AIconGenerator();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
