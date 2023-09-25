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

	/** ��,���ڽ� ���� ��ġ*/
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnPoint;

	/** �� Ŭ���� */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> EnemyClass;

	/** �� ���� */
	virtual void SpawnEnemy();

	/** ���� Ÿ����*/
	FTimerHandle SpawnTimer;

	/** 1�ʿ� �� ��� ����*/
	UPROPERTY(EditAnywhere)
	float SpawnTimeDelay = 1;

	/** ���ڽ�*/

	/** �� Ŭ���� */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHealthBox> HealthBoxClass;

	/** �� ���� */
	virtual void SpawnHealthBox();

	/** ���� Ÿ����*/
	FTimerHandle HealthBoxSpawnTimer;

	/** 1�ʿ� �� ��� ����*/
	UPROPERTY(EditAnywhere)
	float HealthBoxSpawnTimeDelay = 180;

public:	
	
	
};
