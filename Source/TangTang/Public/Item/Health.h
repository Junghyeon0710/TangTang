// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Health.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AHealth : public AItem
{
	GENERATED_BODY()
public:
	AHealth();
protected:

	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
private:

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* HealthParticle;

	UPROPERTY(EditAnywhere)
	float Health = 10;
};
