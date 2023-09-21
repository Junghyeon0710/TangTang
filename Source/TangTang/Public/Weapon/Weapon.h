// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TANGTANG_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	void SetProJectileSpeed(const int TimeDelay);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttachWeapon();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere)
	TArray<class UArrowComponent*> ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent1;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent2;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent3;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent4;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent5;

	UPROPERTY(VisibleAnywhere)
	int32 ArrowIndex = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProJectileClass;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere)
	float SpawnTIme = 1;

	void SpawnProjectile();

	UPROPERTY()
	class AProjectile* Projectile;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;
public:
	FORCEINLINE float GetProjectileSpawnTime() const { return SpawnTIme; }
	FORCEINLINE void SetProjectileSpawnTime(float Time) { SpawnTIme = Time; }
	FORCEINLINE int32 GetArrowIndex() const { return ArrowIndex; }
	FORCEINLINE void SetArrowIndex(int32 GetIndex) { ArrowIndex = GetIndex; }
};
