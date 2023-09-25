// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Health.h"
#include <TangTang/TangTangCharacter.h>
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SphereComponent.h>
AHealth::AHealth()
{
	HealthParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HealthParticle"));
	HealthParticle->SetupAttachment(RootComponent);
	SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AHealth::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
	{
		ATangTangCharacter* Character = Cast<ATangTangCharacter>(OtherActor);
		if (Character)
		{
			Character->HUDHealth((Health + Character->GetHealth())/ Character->GetMaxHelath());
		}
		Destroy();
		if (OverlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, GetActorLocation());
		}
		if (OverlapParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorTransform());
		}
	}
}
