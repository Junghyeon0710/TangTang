// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/HealthPlus.h"
#include <TangTang/TangTangCharacter.h>

void AHealthPlus::SkillExecute(ATangTangCharacter* Character)
{
	if (Character)
	{
		Character->SetMaxHealth(
			Character->GetMaxHelath() +
			(Character->GetMaxHelath() * 0.1)
		);
		Character->HUDHealth(
			Character->GetHealth() /
			Character->GetMaxHelath()
		);
	}
}
