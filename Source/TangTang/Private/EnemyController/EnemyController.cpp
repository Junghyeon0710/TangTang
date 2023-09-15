// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController/EnemyController.h"
#include "Kismet/GameplayStatics.h"


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	

}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToActor(GetWorld()->GetFirstPlayerController(), 10.f);
}

