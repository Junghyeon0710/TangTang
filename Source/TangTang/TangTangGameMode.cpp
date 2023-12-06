// Copyright Epic Games, Inc. All Rights Reserved.

#include "TangTangGameMode.h"
#include "TangTangCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "Enemy.h"
#include "Blueprint/UserWidget.h"


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

void ATangTangGameMode::SpawnEnemy(const FTransform& SpawnTransform)
{
	if(AEnemy::DieNum> BossCount)
	{
		CreateWidget(GetWorld(), BossWidget)->AddToViewport();
		GetWorld()->SpawnActor<AEnemy>(BossEnemy[GameLevel], SpawnTransform);
		AEnemy::DieNum = 0;
		++GameLevel;
	}
	GetWorld()->SpawnActor<AEnemy>(Enemy[GameLevel], SpawnTransform);
}

