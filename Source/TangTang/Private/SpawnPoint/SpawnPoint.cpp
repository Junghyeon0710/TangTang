// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint/SpawnPoint.h"
#include <Components/BoxComponent.h>
#include <Enemy.h>
#include <Kismet/KismetMathLibrary.h>
#include <Item/HealthBox.h>

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Point"));
	SetRootComponent(SpawnPoint);
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnPoint::SpawnEnemy, 1/SpawnTimeDelay, true);
	GetWorldTimerManager().SetTimer(HealthBoxSpawnTimer, this, &ASpawnPoint::SpawnHealthBox, 30, true);
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
	if (HealthBoxClass == nullptr)
	{
		return;
	}

	// ���� ��ġ ���� ����
	FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnPoint->GetComponentLocation(), SpawnPoint->GetScaledBoxExtent());

	// ���� ����
	SpawnLocation.Z = 20;

	// ü�� ���� ����
	GetWorld()->SpawnActor<AHealthBox>(HealthBoxClass, FTransform(SpawnLocation));
}
