// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Lightning.h"
#include <TangTang/TangTangCharacter.h>
#include "Particles/ParticleSystemComponent.h"

ALightning::ALightning()
{
	LightningParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LightningParticle"));
	LightningParticle->SetupAttachment(RootComponent);
}

void ALightning::SkillExecute(ATangTangCharacter* Character)
{
    if (Character == nullptr)
    { 
        return;
    }

    // ĳ���Ϳ��� ���� ������ ����
    TangTangCharacter = Character;
    TangTangCharacter->IncreaseLightningLevel();

    // ���� ��ų�� ����
    LightningSpawn();

    // ĳ���� ���� ��ų ���� Ÿ�̸� ����
    TangTangCharacter->SpawnLightningTimer();
}

void ALightning::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

//���� ��ų�� ����
void ALightning::LightningSpawn()
{
	if (TangTangCharacter)
	{
		TangTangCharacter->SpawnLightning();
	}
}
