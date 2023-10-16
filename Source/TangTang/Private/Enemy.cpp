// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include <Components/BoxComponent.h>
#include <TangTang/TangTangCharacter.h>
#include <Item/SpawnExp.h>

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
}

void AEnemy::GetHit(const float& Damage)
{
	EnemyDie();
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BoxBeginOverlap);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AEnemy::BoxEndOverlap);
}

void AEnemy::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass())) 
	{
		Character = Cast<ATangTangCharacter>(OtherActor);
		if (Character)
		{	
			Character->SetIsEnemyOverlap(true);
			Character->IncreaseOverlapNum();
			Attack();
			int32 OverlapinEnemyNum = Character->GetOverlapNum();
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, 1/ (TimeBasedDamage* OverlapinEnemyNum), true); //1초마다 어택함수 호출
		}
	}
}

void AEnemy::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
	{
		Character = Cast<ATangTangCharacter>(OtherActor);
	
		if (Character && Character->IsEnemyOverlapping())
		{
			Character->DecreaseOverlapNum();
			if (Character->GetOverlapNum() <= 0)
			{
				Character->SetIsEnemyOverlap(false);
				GetWorldTimerManager().ClearTimer(AttackTimer);
			}
		}
	}
}

void AEnemy::EnemyDie()
{
	if (SpawnExpclass)
	{
		SpawnExp = GetWorld()->SpawnActor<ASpawnExp>(SpawnExpclass, GetActorTransform());
		if (SpawnExp)
		{
			SpawnExp->SetSpawnExp(EnemyExp);
		}
		Destroy();
	}
}

void AEnemy::Attack()
{
	if (Character && Character->IsEnemyOverlapping())
	{
		Character->GetDamage(EnemyDamage);
	}
}

