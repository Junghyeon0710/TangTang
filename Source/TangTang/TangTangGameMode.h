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
};



