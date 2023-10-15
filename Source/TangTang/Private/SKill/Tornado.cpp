// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Tornado.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <TangTang/TangTangCharacter.h>
#include "NiagaraComponent.h"

ATornado::ATornado()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 400.f;
	ProjectileMovementComponent->MaxSpeed = 400.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	TornadoNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TornadoNiagara"));
	TornadoNiagara->SetupAttachment(RootComponent);
}

void ATornado::SkillExecute(ATangTangCharacter* Character)
{
	if (Character)
	{
		// 토네이도 인덱스 증가
		Character->IncreaseTornadoIndex();

		// 토네이도 스폰
		Character->SpawnTornado();

		// 토네이도 타이머 실행
		Character->SpawnTornadoTimer();
	}
}

void ATornado::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
