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

public:
	virtual void Tick(float DeltaTime) override;
private:

	/** 캐릭터 반경 몇에서 멈추나*/
	UPROPERTY(EditAnywhere)
	float CharacterRadius = -1;
	
};
