// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnFire.generated.h"

UCLASS()
class TANGTANG_API ASpawnFire : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnFire();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereOverlap;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* FireParticleComponent;

	UPROPERTY(EditAnywhere)
	float FireDamage = 5.f;
};
