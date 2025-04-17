// Copyright Epic Games, Inc. All Rights Reserved.

#include "DKShooterGameMode.h"
#include "DKShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADKShooterGameMode::ADKShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
