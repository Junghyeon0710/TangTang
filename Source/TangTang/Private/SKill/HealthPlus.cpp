// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/HealthPlus.h"
#include <TangTang/TangTangCharacter.h>

void AHealthPlus::SkillExecute(ATangTangCharacter* Character)
{
	if (Character)
	{
		// ���� �ִ� ü���� 10%�� �߰�
		const float MaxHealthIncrease = Character->GetMaxHealth() * 0.1f;
		Character->SetMaxHealth(Character->GetMaxHealth() + MaxHealthIncrease);

		// ü���� ������Ʈ
		const float HealthPercentage = Character->GetHealth() / Character->GetMaxHealth();
		Character->HUDHealth(HealthPercentage);
	}
}
