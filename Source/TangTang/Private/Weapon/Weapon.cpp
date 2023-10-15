// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "../TangTangCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Weapon/Projectile/Projectile.h>
#include <Components/ArrowComponent.h>

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	ArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent1")));
	ArrowComponent[0]->SetupAttachment(RootComponent);

	ArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent2")));
	ArrowComponent[1]->SetupAttachment(RootComponent);

	ArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent3")));
	ArrowComponent[2]->SetupAttachment(RootComponent);

	ArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent4")));
	ArrowComponent[3]->SetupAttachment(RootComponent);

	ArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent5")));
	ArrowComponent[4]->SetupAttachment(RootComponent);

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	AttachWeapon();

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AWeapon::SpawnProjectile, 1 / SpawnTime, true);
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
		Character->SetCharacterWeapon(this);
	}
}

void AWeapon::SetProJectileSpeed(const int TimeDelay)
{
	if (GetWorldTimerManager().IsTimerActive(SpawnTimer))
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
	SpawnTime = TimeDelay;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AWeapon::SpawnProjectile, 1 / SpawnTime, true);
}

void AWeapon::SpawnProjectile()
{
	if (ProjectileClass == nullptr) return;

	// 화살 인덱스가 5를 넘지 않도록 보정
	if (ArrowIndex > 4) ArrowIndex = 4;

	for(int32 Arrowi = 0; Arrowi <= ArrowIndex; Arrowi++)
	{	
		FTransform SpawnTransform = ArrowComponent[Arrowi]->GetComponentTransform();
		Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnTransform);
		
		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				FireSound,
				Projectile->GetActorLocation());
		}

		if (Projectile)
		{
			Projectile->SetLifeSpan(5.f);
		}
	}
}

