// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetHealthBar(float Health);
	void SetTime(float DeltaTime);
	void SetExpBar(float Exp);

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Time;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ExpBar;

	
};
