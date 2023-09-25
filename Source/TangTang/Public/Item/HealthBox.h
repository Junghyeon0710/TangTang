// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "HealthBox.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AHealthBox : public AItem
{
	GENERATED_BODY()

	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHealth> HealthClass;
};
