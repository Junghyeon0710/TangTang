// Copyright Epic Games, Inc. All Rights Reserved.

#include "TangTangGameMode.h"
#include "TangTangCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>


ATangTangGameMode::ATangTangGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATangTangGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (TangTangBGM)
	{
		UGameplayStatics::PlaySound2D(this, TangTangBGM);
	}
}
