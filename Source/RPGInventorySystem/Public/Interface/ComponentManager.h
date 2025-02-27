// Copyright by liclem97.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComponentManager.generated.h"

class UInventoryComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UComponentManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGINVENTORYSYSTEM_API IComponentManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	UInventoryComponent* GetInventoryComponent() const;

};
