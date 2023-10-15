// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Skill.h"
#include <Components/SphereComponent.h>
#include <HitInterface.h>
#include <Kismet/GameplayStatics.h>

ASkill::ASkill()
{
	// 기본 틱 비활성화
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	SetRootComponent(SphereOverlap);
	
	// 충돌 구역 설정
	SphereOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);

	// 스킬 메쉬 설정
	SkillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GuardianMEsh"));
	SkillMesh->SetupAttachment(RootComponent);
	SkillMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASkill::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 이벤트 설정
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &ASkill::SphereBeginOverlap);
	SphereOverlap->OnComponentEndOverlap.AddDynamic(this, &ASkill::SphereOverlapEnd);
}

void ASkill::SkillExecute(ATangTangCharacter* Character)
{
	if (SkillExecuteSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SkillExecuteSound, GetActorLocation());
	}
}

void ASkill::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// HitInterface를 구현한 액터인지 확인
		IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			// 데미지 적용
			HitInterface->GetHit(SkillDamage);

			// 오버랩 사운드 재생
			if (SkillOverlapSound)
			{
				UGameplayStatics::PlaySound2D(this, SkillOverlapSound);
			}

			// 오버랩 파티클 스폰
			if (SkillOverlapParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillOverlapParticle, OtherActor->GetTransform());
			}
		}
	}
}

void ASkill::SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 자식 클래스에서 구현
}


