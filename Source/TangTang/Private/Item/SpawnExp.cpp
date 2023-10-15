// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SpawnExp.h"
#include <Components/SphereComponent.h>
#include <TangTang/TangTangCharacter.h>

ASpawnExp::ASpawnExp()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	SetRootComponent(SphereOverlap);

	EXPMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EXPMesh"));
	EXPMesh->SetupAttachment(RootComponent);
}

void ASpawnExp::BeginPlay()
{
	Super::BeginPlay();
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &ASpawnExp::SphereBeginOverlap);
}

void ASpawnExp::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
	{
		ATangTangCharacter* Character = Cast<ATangTangCharacter>(OtherActor);
		if (Character)
		{
			Character->GetExp(SpawnExp);
			Destroy();
		}
	}
}
