// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TangTangGameMode.generated.h"

UCLASS(minimalapi)
class ATangTangGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATangTangGameMode();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class USoundBase* TangTangBGM;

	
	UPROPERTY(EditAnywhere)
	int32 GameLevel = 0;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEnemy>> Enemy;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEnemy>> BossEnemy;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> BossWidget;

	int32 BossCount = 150;
public:

	void SpawnEnemy(const FTransform& SpawnTransform);
};



