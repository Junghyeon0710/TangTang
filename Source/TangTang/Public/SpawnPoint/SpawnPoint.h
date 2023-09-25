// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class TANGTANG_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnPoint();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

	/** 적,힐박스 스폰 위치*/
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnPoint;

	/** 적 클래스 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> EnemyClass;

	/** 적 스폰 */
	virtual void SpawnEnemy();

	/** 스폰 타이퍼*/
	FTimerHandle SpawnTimer;

	/** 1초에 적 몇명 스폰*/
	UPROPERTY(EditAnywhere)
	float SpawnTimeDelay = 1;

	/** 힐박스*/

	/** 힐 클래스 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHealthBox> HealthBoxClass;

	/** 적 스폰 */
	virtual void SpawnHealthBox();

	/** 스폰 타이퍼*/
	FTimerHandle HealthBoxSpawnTimer;

	/** 1초에 적 몇명 스폰*/
	UPROPERTY(EditAnywhere)
	float HealthBoxSpawnTimeDelay = 180;

public:	
	
	
};
