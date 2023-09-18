// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnExp.generated.h"

UCLASS()
class TANGTANG_API ASpawnExp : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnExp();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereOverlap;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EXPMesh;
	
	UPROPERTY(VisibleAnywhere)
	float SpawnExp = 0.f;

public:
	FORCEINLINE float GetSpawnExp() const { return SpawnExp; }
	FORCEINLINE void SetSpawnExp(float Exp) {SpawnExp = Exp; }
};
