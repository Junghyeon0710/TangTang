// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TANGTANG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereOverlap;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	class USoundBase* OverlapSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* OverlapParticle;

};
