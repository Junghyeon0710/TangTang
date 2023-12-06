// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitInterface.h"
#include "Enemy.generated.h"


UCLASS()
class TANGTANG_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void GetHit(const float& Damage)override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BoxBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//스페어 콜리저에서 떨어질시
	UFUNCTION()
	virtual void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//적 죽을시
	void EnemyDie();

private:

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	float EnemyDamage = 5.f;

	/** 데미지 어택 타이머*/
	FTimerHandle AttackTimer;

	bool OverlapCharacter = false;

	UPROPERTY(EditAnywhere)
	float TimeBasedDamage = 1.f;

	void Attack(); 
	/*****************/
	
	UPROPERTY()
	class ATangTangCharacter* Character;

	/** 적 체력 */
	UPROPERTY(EditAnywhere)
	float EnemyMaxHealth = 10.f;

	UPROPERTY(EditAnywhere)
	float EnemyHealth = 10.f;

	//적 경험치
	UPROPERTY(EditAnywhere)
	float EnemyExp = 10.f;

	/** 적 죽을시 경험치 액터 스폰*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpawnExp> SpawnExpclass;

	UPROPERTY()
	class ASpawnExp* SpawnExp = SpawnExp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticle;

	

public:
	static int32 DieNum;
};
int32 AEnemy::DieNum = 0;
