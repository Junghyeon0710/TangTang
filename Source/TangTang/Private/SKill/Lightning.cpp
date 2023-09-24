// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Lightning.h"
#include <TangTang/TangTangCharacter.h>
#include "Particles/ParticleSystemComponent.h"

ALightning::ALightning()
{
	LightningPartcle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LightningPartcle"));
	LightningPartcle->SetupAttachment(RootComponent);
}

void ALightning::SkillExecute(ATangTangCharacter* Character)
{
	if (Character == nullptr) return;
	TangTangCharacter = Character;
	TangTangCharacter->SetLightningLevel(
		TangTangCharacter->GetLightningLevel() + 1);
	LightningSpawn();
	TangTangCharacter->SpawnLightningTimer();

}

void ALightning::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ALightning::LightningSpawn()
{
	if (TangTangCharacter)
	{
		TangTangCharacter->SpawnLightning();
	}
}


