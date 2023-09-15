// Copyright Epic Games, Inc. All Rights Reserved.

#include "TangTangGameMode.h"
#include "TangTangCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATangTangGameMode::ATangTangGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
