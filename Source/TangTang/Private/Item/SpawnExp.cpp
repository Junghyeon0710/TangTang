// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SpawnExp.h"
#include <Components/SphereComponent.h>
#include <TangTang/TangTangCharacter.h>
// Sets default values
ASpawnExp::ASpawnExp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	SetRootComponent(SphereOverlap);

	EXPMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EXPMesh"));
	EXPMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
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

// Called every frame
void ASpawnExp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}