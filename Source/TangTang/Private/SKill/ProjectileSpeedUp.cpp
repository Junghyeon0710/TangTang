// Fill out your copyright notice in the Description page of Project Settings.


#include "SKill/ProjectileSpeedUp.h"
#include <TangTang/TangTangCharacter.h>
#include <Weapon/Weapon.h>

void AProjectileSpeedUp::SkillExecute(ATangTangCharacter* Character)
{
    if (Character && Character->GetCharacterWeapon())
    {
        AWeapon* CharacterWeapon = Character->GetCharacterWeapon();
        if (CharacterWeapon)
        {
            float NewProjectileSpeed = CharacterWeapon->GetProjectileSpawnTime() * 2;
            CharacterWeapon->SetProJectileSpeed(NewProjectileSpeed);
        }
    }
}
