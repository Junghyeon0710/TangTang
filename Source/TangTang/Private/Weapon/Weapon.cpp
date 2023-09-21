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
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	ArrowComponent1 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent1"));
	ArrowComponent1->SetupAttachment(RootComponent);

	ArrowComponent2 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent2"));
	ArrowComponent2->SetupAttachment(RootComponent);

	ArrowComponent3 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent3"));
	ArrowComponent3->SetupAttachment(RootComponent);

	ArrowComponent4 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent4"));
	ArrowComponent4->SetupAttachment(RootComponent);

	ArrowComponent5 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent5"));
	ArrowComponent5->SetupAttachment(RootComponent);
	
	ArrowComponent.Add(ArrowComponent1);
	ArrowComponent.Add(ArrowComponent2);
	ArrowComponent.Add(ArrowComponent3);
	ArrowComponent.Add(ArrowComponent4);
	ArrowComponent.Add(ArrowComponent5);
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
		Character->SetCharacterWeapon(this);
	}

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SetProJectileSpeed(const int TimeDelay)
{
	if (GetWorldTimerManager().IsTimerActive(SpawnTimer))
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
	SpawnTIme = TimeDelay;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AWeapon::SpawnProjectile, 1 / SpawnTIme, true);
}

void AWeapon::SpawnProjectile()
{
	if (ProJectileClass == nullptr) return;

	if (ArrowIndex == 5) ArrowIndex = 4;
	for(int32 Arrowi = 0; Arrowi <= ArrowIndex; Arrowi++)
	{	
		Projectile = GetWorld()->SpawnActor<AProjectile>(ProJectileClass, ArrowComponent[Arrowi]->GetComponentTransform());
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

