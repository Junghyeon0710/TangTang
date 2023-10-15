// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/Skill.h"
#include <Components/SphereComponent.h>
#include <HitInterface.h>
#include <Kismet/GameplayStatics.h>

ASkill::ASkill()
{
	// �⺻ ƽ ��Ȱ��ȭ
	PrimaryActorTick.bCanEverTick = false;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	SetRootComponent(SphereOverlap);
	
	// �浹 ���� ����
	SphereOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);

	// ��ų �޽� ����
	SkillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GuardianMEsh"));
	SkillMesh->SetupAttachment(RootComponent);
	SkillMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASkill::BeginPlay()
{
	Super::BeginPlay();

	// �浹 �̺�Ʈ ����
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
		// HitInterface�� ������ �������� Ȯ��
		IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			// ������ ����
			HitInterface->GetHit(SkillDamage);

			// ������ ���� ���
			if (SkillOverlapSound)
			{
				UGameplayStatics::PlaySound2D(this, SkillOverlapSound);
			}

			// ������ ��ƼŬ ����
			if (SkillOverlapParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillOverlapParticle, OtherActor->GetTransform());
			}
		}
	}
}

void ASkill::SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// �ڽ� Ŭ�������� ����
}


