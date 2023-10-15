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

    // 캐릭터에게 번개 레벨을 증가
    TangTangCharacter = Character;
    TangTangCharacter->IncreaseLightningLevel();

    // 번개 스킬을 생성
    LightningSpawn();

    // 캐릭터 번개 스킬 생성 타이머 시작
    TangTangCharacter->SpawnLightningTimer();
}

void ALightning::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

//번개 스킬을 생성
void ALightning::LightningSpawn()
{
	if (TangTangCharacter)
	{
		TangTangCharacter->SpawnLightning();
	}
}
