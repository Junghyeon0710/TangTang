// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SKill/Skill.h"
#include "HealthPlus.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AHealthPlus : public ASkill
{
	GENERATED_BODY()
public:
	virtual void SkillExecute(class ATangTangCharacter* Character) override;
};
