// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyController/EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include <Components/BoxComponent.h>
#include <TangTang/TangTangCharacter.h>

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
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
			Index++;
			EndTimer.Add(FTimerHandle());
			DamageTimer.Add(Index, OverlappedComp);
			GetWorldTimerManager().SetTimer(EndTimer[Index], this, &AEnemy::Attack, DamageTime, true);
		}
	}
}

void AEnemy::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
	{
		if (DamageTimer.Num() > 0)
		{
			for (auto& Dmage : DamageTimer)
			{
				if (Dmage.Value == OverlappedComponent)
				{
					GetWorldTimerManager().ClearTimer(EndTimer[Dmage.Key]);
				}

			}
		}

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
	if (Character)
	{
		Character->GetDamage(EnemyDamage);
	}
}

