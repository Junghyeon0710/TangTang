// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyController/EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include <Components/BoxComponent.h>
#include <TangTang/TangTangCharacter.h>
#include <Item/SpawnExp.h>

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
}

void AEnemy::GetHit(const float& Damage)
{
	EnemyDie();
	
}

// Called when the game starts or when spawned
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
			Character->SetEnemyOverlap(true);
			Character->SetOverlapNum(Character->GetOverlapNum() + 1);
			Attack();
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEnemy::Attack, 1/ DamageTime, true); //1초마다 어택함수 호출
		}
	}
}

void AEnemy::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
	{
		Character = Cast<ATangTangCharacter>(OtherActor);
	
		if (Character && Character->GetEnemyOverlap())
		{
			Character->SetEnemyOverlap(false);
			Character->SetOverlapNum(Character->GetOverlapNum() -1);
			if (Character->GetOverlapNum() < 0)
			{
				GetWorldTimerManager().ClearTimer(EndTimer);
			}
		}
		if (Character->GetOverlapNum() > 0)
		{
			Character->SetEnemyOverlap(true);
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

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Attack()
{
	if (Character && Character->GetEnemyOverlap())
	{
		Character->GetDamage(EnemyDamage);
	}
}

