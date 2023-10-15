// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/HealthPlus.h"
#include <TangTang/TangTangCharacter.h>

void AHealthPlus::SkillExecute(ATangTangCharacter* Character)
{
	if (Character)
	{
		// 현재 최대 체력의 10%를 추가
		const float MaxHealthIncrease = Character->GetMaxHealth() * 0.1f;
		Character->SetMaxHealth(Character->GetMaxHealth() + MaxHealthIncrease);

		// 체력을 업데이트
		const float HealthPercentage = Character->GetHealth() / Character->GetMaxHealth();
		Character->HUDHealth(HealthPercentage);
	}
}
