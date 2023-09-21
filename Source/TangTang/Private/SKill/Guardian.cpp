// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Guardian.h"
#include <Kismet/GameplayStatics.h>
#include <TangTang/TangTangCharacter.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/SphereComponent.h>
#include <HitInterface.h>


AGuardian::AGuardian()
{
	PrimaryActorTick.bCanEverTick = true;

	GuardianRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GuardainRoot"));
	SetRootComponent(GuardianRoot);

	SphereOverlap->SetupAttachment(RootComponent);
	SkillMesh->SetupAttachment(SphereOverlap);

}

void AGuardian::BeginPlay()
{
	Super::BeginPlay();

	 TangTangCharacter = Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void AGuardian::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherActor)
	{
		HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			HitInterface->GetHit(SkillDamage);
			GetWorldTimerManager().SetTimer(
				GuardianDamageTimer,
				this,
				&AGuardian::GuardianDamage,
				1 / GuardianDamageTiemDelay,
				true);
		}
	}*/
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AGuardian::SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (GetWorldTimerManager().IsTimerActive(GuardianDamageTimer))
	{
		GetWorldTimerManager().ClearTimer(GuardianDamageTimer);
	}*/
	if (HitInterface)
	{
		HitInterface = nullptr;
	}
}

void AGuardian::SkillExecute(ATangTangCharacter* Character)
{
	if (Character)
	{
		Character->GuardianSpawn();
	}
	Super::SkillExecute(Character);
}

void AGuardian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AroundCharacter();
	
}

void AGuardian::AroundCharacter()
{
	TangTangCharacter = TangTangCharacter == nullptr ? Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) : TangTangCharacter;

	if (TangTangCharacter)
	{
		SetActorLocation(TangTangCharacter->GetActorLocation());
		SphereOverlap->SetRelativeLocation(
			FVector(UKismetMathLibrary::DegCos(Time) * RadiusX,
				UKismetMathLibrary::DegSin(Time) * RadiusY,
				0.f));
		if (GetWorld()->DeltaTimeSeconds * Speed + Time > 360.f)
		{
			Time = 0;
		}
		else
		{
			Time = GetWorld()->DeltaTimeSeconds * Speed + Time;
		}
	}
}

void AGuardian::GuardianDamage()
{
	if (HitInterface)
	{
		HitInterface->GetHit(SkillDamage);
	}
}

