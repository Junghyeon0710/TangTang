// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HealthBox.h"
#include <Item/Health.h>
#include <Weapon/Projectile/Projectile.h>
#include <Kismet/GameplayStatics.h>
void AHealthBox::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
		if (HealthClass)
		{
			GetWorld()->SpawnActor<AHealth>(HealthClass, GetActorTransform());
		}
		Destroy();
	}

}
