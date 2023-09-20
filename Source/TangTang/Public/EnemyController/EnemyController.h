// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AEnemyController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
private:

	/** ĳ���� �ݰ� ��� ���߳�*/
	UPROPERTY(EditAnywhere)
	float Radius = -1;
	
};