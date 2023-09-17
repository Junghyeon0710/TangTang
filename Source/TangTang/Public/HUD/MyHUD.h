// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AMyHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterOverlay* CharacterOverlay;
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCharacterOverlay> CharacterOverlayclass;

public:
	FORCEINLINE UCharacterOverlay* GetCharacterOverlay() const { return CharacterOverlay; }
};
