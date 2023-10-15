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
	Super::SphereBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AGuardian::SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
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

	UpdateGuardianLocation();
}

void AGuardian::UpdateGuardianLocation()
{
	// 플레이어 캐릭터 레퍼런스 획득
	TangTangCharacter = TangTangCharacter == nullptr ? Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) : TangTangCharacter;

	if (TangTangCharacter)
	{
		// 가디언의 위치 설정
		SetActorLocation(TangTangCharacter->GetActorLocation());

		// 가디언의 스피어 컴포넌트 위치 설정
		SphereOverlap->SetRelativeLocation(FVector(
			UKismetMathLibrary::DegCos(GuardianTime) * GuardianRadiusX,
			UKismetMathLibrary::DegSin(GuardianTime) * GuardianRadiusY,
			0.f));

		// 가디언 시간 업데이트
		if (GetWorld()->DeltaTimeSeconds * GuardianSpeed + GuardianTime > 360.f)
		{
			GuardianTime = 0;
		}
		else
		{
			GuardianTime = GetWorld()->DeltaTimeSeconds * GuardianSpeed + GuardianTime;
		}
	}
}

void AGuardian::GuardianDamage()
{
	if (HitInterface)
	{
		// 겹쳐있는 적에게 데미지 적용
		HitInterface->GetHit(SkillDamage);
	}
}

