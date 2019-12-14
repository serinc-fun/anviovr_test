// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AnvioVRTestProjectGameMode.h"
#include "AnvioVRTestProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAnvioVRTestProjectGameMode::AAnvioVRTestProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
