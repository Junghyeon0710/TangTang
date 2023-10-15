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

	// 스폰 위치 랜덤 선택
	FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnPoint->GetComponentLocation(), SpawnPoint->GetScaledBoxExtent());

	// 높이 조정
	SpawnLocation.Z = 20;

	// 체력 상자 스폰
	GetWorld()->SpawnActor<AHealthBox>(HealthBoxClass, FTransform(SpawnLocation));
}
