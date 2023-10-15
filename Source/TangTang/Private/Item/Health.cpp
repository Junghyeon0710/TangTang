// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Health.h"
#include "TangTang/TangTangCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

AHealth::AHealth()
{
    // Health �����ۿ� ���� �⺻ ����
    HealthParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HealthParticle"));
    HealthParticle->SetupAttachment(RootComponent);

    // SphereOverlap �浹 ä���� ����
    SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AHealth::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // �ٸ� ���Ϳ��� �浹 ���θ� Ȯ��
    if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
    {
        // �ٸ� ���Ͱ� TangTangCharacter Ŭ������ �ν��Ͻ��� ��� Character �����ͷ� ĳ����
        ATangTangCharacter* Character = Cast<ATangTangCharacter>(OtherActor);

        if (Character)
        {
            // Character�� ü���� ������Ʈ
            float NewHealth = (HealthIncrease + Character->GetHealth()) / Character->GetMaxHealth();
            Character->HUDHealth(NewHealth);
        }

        // �������� �ı�
        Destroy();

        // ������ ���带 ���
        if (OverlapSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, GetActorLocation());
        }

        // ������ ��ƼŬ�� ����
        if (OverlapParticle)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorTransform());
        }
    }
}