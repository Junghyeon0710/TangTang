// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/CharacterOverlay.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>


void UCharacterOverlay::SetHealthBar(float Health)
{
	if (HealthBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health:%f"),Health);
		HealthBar->SetPercent(Health);
	}
	
}

void UCharacterOverlay::SetTime(float DeltaTime)
{
	FString TimeSecond = FString::Printf(TEXT("%.2f"), DeltaTime);
	Time->SetText(FText::FromString(TimeSecond));
}
