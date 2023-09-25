// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Molotovcocktail.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/SphereComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include <TangTang/TangTangCharacter.h>
#include <SKill/DestroyActor/SpawnFire.h>
#include <Kismet/GameplayStatics.h>

AMolotovcocktail::AMolotovcocktail()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 400.f;
	ProjectileMovementComponent->MaxSpeed = 400.f;

	SphereOverlap->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereOverlap->bHasPerInstanceHitProxies = true;
	SphereOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	FireParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticle"));
	FireParticle->SetupAttachment(RootComponent);
}

void AMolotovcocktail::SkillExecute(ATangTangCharacter* Character)
{
	if (Character == nullptr) return;

	Character->SetMolotovconcktailIndex(Character->GetMolotovconcktailIndex() + 1);
	Character->SpawnMolotovcoktail();
	Character->SpawnMolotovcoktailTimer();
}

void AMolotovcocktail::BeginPlay()
{
	Super::BeginPlay();

	SphereOverlap->OnComponentHit.AddDynamic(this, &AMolotovcocktail::OnHit);
}

void AMolotovcocktail::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	if (SpawnFireClass)
	{
		ASpawnFire* SpawnFire = GetWorld()->SpawnActor<ASpawnFire>(SpawnFireClass, GetActorTransform());
		if (SpawnFire)
		{
			SpawnFire->SetLifeSpan(3.f);
		}
		if (SpawnFireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SpawnFireSound, SpawnFire->GetActorLocation());

		}

	}
}
