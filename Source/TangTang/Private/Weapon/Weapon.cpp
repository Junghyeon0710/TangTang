// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "../TangTangCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Weapon/Projectile/Projectile.h>
#include <Components/ArrowComponent.h>
// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	AttachWeapon();
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AWeapon::SpawnProjectile, 1 / SpawnTIme, true);
}

void AWeapon::AttachWeapon()
{
	ATangTangCharacter* Character = Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget,true);

		this->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, FName("WeaponSocket"));
		SetOwner(Character);
		SetInstigator(Character);
	}

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SpawnProjectile()
{
	if (ProJectileClass)
	{
		Projectile = GetWorld()->SpawnActor<AProjectile>(ProJectileClass, ArrowComponent->GetComponentTransform());
		if (Projectile)
		{
			Projectile->SetLifeSpan(5.f);
		}
	}

}

