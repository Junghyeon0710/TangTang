// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/DestroyActor/SpawnFire.h"
#include <Components/SphereComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include <HitInterface.h>

// Sets default values
ASpawnFire::ASpawnFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereOverlap"));
	SetRootComponent(SphereOverlap);

	FireParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleComponent"));
	FireParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawnFire::BeginPlay()
{
	Super::BeginPlay();
	
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &ASpawnFire::SphereBeginOverlap);
}

void ASpawnFire::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			HitInterface->GetHit(FireDamage);
		}
	}
}

// Called every frame
void ASpawnFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

