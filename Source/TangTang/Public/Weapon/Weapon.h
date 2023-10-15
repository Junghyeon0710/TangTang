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
	/** 프로젝타일 속도 설정 함수 */
	void SetProJectileSpeed(const int TimeDelay);

protected:
	virtual void BeginPlay() override;

	/** 무기를 캐릭터에 부착하는 함수 */
	void AttachWeapon();

private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WeaponMesh;

	/** 프로젝타일을 발사하는 위치를 알려주는 화살 컴포넌트 배열 */
	UPROPERTY(VisibleAnywhere)
	TArray<class UArrowComponent*> ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	int32 ArrowIndex = 0;

	/** 프로젝타일 클래스 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	/** 프로젝타일 스폰 타이머 핸들 */
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
