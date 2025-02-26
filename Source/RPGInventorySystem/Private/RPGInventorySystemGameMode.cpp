// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGInventorySystemGameMode.h"
#include "RPGInventorySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGInventorySystemGameMode::ARPGInventorySystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
