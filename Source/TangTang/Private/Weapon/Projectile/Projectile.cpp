// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/SphereComponent.h>
#include <Enemy.h>
#include <HitInterface.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	Projectile->SetupAttachment(RootComponent);
	Projectile->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Projectile->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Projectile->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Projectile->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(AEnemy::StaticClass()))
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			HitInterface->GetHit(Damage);	
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(
					this,
					HitSound,
					OtherActor->GetActorLocation()
				);
			}
			if (HitParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(
					GetWorld(),
					HitParticle,
					OtherActor->GetTransform()
				);
			}
			Destroy();
		}
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}