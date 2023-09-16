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
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProJectileClass;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere)
	float SpawnTIme = 1;

	void SpawnProjectile();

	UPROPERTY()
	class AProjectile* Projectile;
};
