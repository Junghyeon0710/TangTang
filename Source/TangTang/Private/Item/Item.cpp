// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include <Components/SphereComponent.h>	
#include <Weapon/Projectile/Projectile.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
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

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

