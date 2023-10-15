// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController/EnemyController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn, CharacterRadius, false);
        SetFocus(PlayerPawn);
    }
}

