// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SKill/Skill.h"
#include "ProjectileSpeedUp.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AProjectileSpeedUp : public ASkill
{
	GENERATED_BODY()
public:
	virtual void SkillExecute(class ATangTangCharacter* Character) override;
};
