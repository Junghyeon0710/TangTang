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
	AWeapon();
	/** ������Ÿ�� �ӵ� ���� �Լ� */
	void SetProJectileSpeed(const int TimeDelay);

protected:
	virtual void BeginPlay() override;

	/** ���⸦ ĳ���Ϳ� �����ϴ� �Լ� */
	void AttachWeapon();

private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WeaponMesh;

	/** ������Ÿ���� �߻��ϴ� ��ġ�� �˷��ִ� ȭ�� ������Ʈ �迭 */
	UPROPERTY(VisibleAnywhere)
	TArray<class UArrowComponent*> ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	int32 ArrowIndex = 0;

	/** ������Ÿ�� Ŭ���� */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	/** ������Ÿ�� ���� Ÿ�̸� �ڵ� */
	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere)
	float SpawnTime = 1;

	void SpawnProjectile();


	UPROPERTY()
	class AProjectile* Projectile;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

public:
	FORCEINLINE float GetProjectileSpawnTime() const { return SpawnTime; }
	FORCEINLINE void SetProjectileSpawnTime(float Time) { SpawnTime = Time; }
	FORCEINLINE void IncreaseArrowIndex() { ArrowIndex++; }
};
