// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint/SpawnPoint.h"
#include <Components/BoxComponent.h>
#include <Enemy.h>
#include <Kismet/KismetMathLibrary.h>
#include <Item/HealthBox.h>

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Point"));
	SetRootComponent(SpawnPoint);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnPoint::SpawnEnemy, 1/SpawnTimeDelay, true);
	GetWorldTimerManager().SetTimer(HealthBoxSpawnTimer, this, &ASpawnPoint::SpawnHealthBox, HealthBoxSpawnTimeDelay, true,1.f);
}

void ASpawnPoint::SpawnEnemy()
{
	if (EnemyClass)
	{
		FVector BoxRandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(SpawnPoint->GetComponentLocation(), SpawnPoint->GetScaledBoxExtent()); 
		GetWorld()->SpawnActor<AEnemy>(EnemyClass, FTransform(BoxRandomPoint));
	}
}

void ASpawnPoint::SpawnHealthBox()
{
	if (HealthBoxClass)
	{
		FVector BoxRandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(SpawnPoint->GetComponentLocation(), SpawnPoint->GetScaledBoxExtent());
		AHealthBox* HealthBox = GetWorld()->SpawnActor<AHealthBox>(HealthBoxClass, FTransform(BoxRandomPoint));
		FVector HelathBoxLocation = BoxRandomPoint;
		HelathBoxLocation.Z = 20;
		if (HealthBox)
		{
			HealthBox->SetActorLocation(HelathBoxLocation);
		}
	}
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

