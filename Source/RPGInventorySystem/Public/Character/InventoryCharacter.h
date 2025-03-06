// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ComponentManager.h"
#include "InventoryCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInventoryComponent;
class USceneCaptureComponent2D;

UCLASS()
class RPGINVENTORYSYSTEM_API AInventoryCharacter : public ACharacter, public IComponentManager
{
	GENERATED_BODY()

public:
	AInventoryCharacter();

	void SwapSword(UStaticMesh* InSword);
	void SwapShield(UStaticMesh* InShield);
	void SwapHelmet(UStaticMesh* InHelmet);
	void SwapArmour(USkeletalMesh* InArmour);
	void SwapPants(USkeletalMesh* InPants);
	void SwapBoots(USkeletalMesh* InBoots);

	/** Component Manager Interface */
	FORCEINLINE virtual UInventoryComponent* GetInventoryComponent_Implementation() const override { return InventoryComponent; }
	FORCEINLINE virtual AInventoryCharacter* GetPlayerCharacter_Implementation() override { return this; }
	/** End Component Manager Interface */

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UStaticMesh* GetEmptyMesh() const { return EmptyMesh; }
	FORCEINLINE USkeletalMesh* GetEmptySkeletalMesh() const { return EmptySkeletalMesh; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, Category = Socket)
	UStaticMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere, Category = Socket)
	UStaticMeshComponent* ShieldMesh;

	UPROPERTY(EditAnywhere, Category = Socket)
	UStaticMeshComponent* HelmetMesh;

	UPROPERTY(EditAnywhere, Category = Socket)
	USkeletalMeshComponent* ArmourMesh;

	UPROPERTY(EditAnywhere, Category = Socket)
	USkeletalMeshComponent* PantsMesh;

	UPROPERTY(EditAnywhere, Category = Socket)
	USkeletalMeshComponent* BootsMesh;

	UPROPERTY(EditAnywhere, Category = Camera)
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(EditAnywhere)
	UStaticMesh* EmptyMesh;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* EmptySkeletalMesh;
};
