// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Skill.h"
#include <Components/SphereComponent.h>
#include <HitInterface.h>
// Sets default values
ASkill::ASkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject <USphereComponent>(TEXT("Overlap"));
	SphereOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereOverlap);

	SkillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GuardianMEsh"));
	SkillMesh->SetupAttachment(RootComponent);
	SkillMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASkill::BeginPlay()
{
	Super::BeginPlay();
	
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &ASkill::SphereBeginOverlap);
	SphereOverlap->OnComponentEndOverlap.AddDynamic(this, &ASkill::SphereOverlapEnd);
}

void ASkill::SkillExecute(ATangTangCharacter* Character)
{
}

void ASkill::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			HitInterface->GetHit(SkillDamage);
		}
	}
}

void ASkill::SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

