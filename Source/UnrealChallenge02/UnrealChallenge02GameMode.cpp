// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealChallenge02GameMode.h"
#include "UnrealChallenge02Character.h"
#include "UObject/ConstructorHelpers.h"

AUnrealChallenge02GameMode::AUnrealChallenge02GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
