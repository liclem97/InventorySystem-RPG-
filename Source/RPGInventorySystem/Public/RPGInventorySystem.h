// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RPGInventorySystem.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USkeletalMesh* SkeletalMesh;
};

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	Armour_Equipment UMETA(DisplayName = "Armour & Equipment"),
	Consumeables UMETA(DisplayName = "Consumeables")
};

USTRUCT(BlueprintType)
struct FItemMaster : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FDataTableRowHandle DataTable = FDataTableRowHandle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EItemTypes ItemType = EItemTypes();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Quantity = 0;
};