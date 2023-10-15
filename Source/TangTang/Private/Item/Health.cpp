// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Health.h"
#include "TangTang/TangTangCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

AHealth::AHealth()
{
    // Health 아이템에 대한 기본 설정
    HealthParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HealthParticle"));
    HealthParticle->SetupAttachment(RootComponent);

    // SphereOverlap 충돌 채널을 설정
    SphereOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AHealth::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 다른 액터와의 충돌 여부를 확인
    if (OtherActor && OtherActor->IsA(ATangTangCharacter::StaticClass()))
    {
        // 다른 액터가 TangTangCharacter 클래스의 인스턴스인 경우 Character 포인터로 캐스팅
        ATangTangCharacter* Character = Cast<ATangTangCharacter>(OtherActor);

        if (Character)
        {
            // Character의 체력을 업데이트
            float NewHealth = (HealthIncrease + Character->GetHealth()) / Character->GetMaxHealth();
            Character->HUDHealth(NewHealth);
        }

        // 아이템을 파괴
        Destroy();

        // 오버랩 사운드를 재생
        if (OverlapSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, GetActorLocation());
        }

        // 오버랩 파티클을 생성
        if (OverlapParticle)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorTransform());
        }
    }
}