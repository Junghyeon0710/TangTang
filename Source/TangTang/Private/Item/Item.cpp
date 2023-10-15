// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Item.h"
#include <Components/SphereComponent.h>	
#include <Weapon/Projectile/Projectile.h>
#include <Kismet/GameplayStatics.h>

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	SetRootComponent(SphereOverlap);

	SphereOverlap->SetGenerateOverlapEvents(true);
	SphereOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &AItem::SphereBeginOverlap);
}

void AItem::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AProjectile::StaticClass()))
	{
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
