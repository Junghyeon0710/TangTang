// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Tornado.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <TangTang/TangTangCharacter.h>
#include "NiagaraComponent.h"

ATornado::ATornado()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 400.f;
	ProjectileMovementComponent->MaxSpeed = 400.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	TornadoParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TornadoParticle"));
	TornadoParticle->SetupAttachment(RootComponent);
}

void ATornado::SkillExecute(ATangTangCharacter* Character)
{
	if (Character == nullptr) return;
	Character->SetTornadoIndex(Character->GetTornadoIndex() + 1);
	Character->SpawnTornado();
	Character->SpawnTorandoTimer();
	
}

void ATornado::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
