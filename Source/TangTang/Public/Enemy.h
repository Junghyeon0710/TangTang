// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TANGTANG_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BoxBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//스페어 콜리저에서 떨어질시
	UFUNCTION()
	virtual void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	UPROPERTY(VisibleAnywhere)
	class AAIController* EnemyController;

	//* 반경 몇에서 멈추나*
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 5.f;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	float EnemyDamage = 5.f;

	TMap<int32, UPrimitiveComponent*> DamageTimer;
	TArray<FTimerHandle> EndTimer;

	void Attack();

	UPROPERTY(EditAnywhere)
	float DamageTime = 1.f;


	int32 Index = -1;

	int32 Overlaping = 0;

	UPROPERTY()
	class ATangTangCharacter* Character;
};
