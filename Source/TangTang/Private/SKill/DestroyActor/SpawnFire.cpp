// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/DestroyActor/SpawnFire.h"
#include <Components/SphereComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include <HitInterface.h>

ASpawnFire::ASpawnFire()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereOverlap"));
	SetRootComponent(SphereOverlap);

	FireParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleComponent"));
	FireParticleComponent->SetupAttachment(RootComponent);
}

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

