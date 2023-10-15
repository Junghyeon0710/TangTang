// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/ProjectilePlus.h"
#include <TangTang/TangTangCharacter.h>
#include <Weapon/Weapon.h>

void AProjectilePlus::SkillExecute(ATangTangCharacter* Character)
{
	if (Character)
	{
		AWeapon* CharacterWeapon = Character->GetCharacterWeapon();
		if (CharacterWeapon)
		{
			CharacterWeapon->IncreaseArrowIndex();
		}
	}
}
