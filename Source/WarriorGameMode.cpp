// Copyright Epic Games, Inc. All Rights Reserved.

#include "WarriorGameMode.h"
#include "WarriorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWarriorGameMode::AWarriorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
