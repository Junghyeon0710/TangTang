// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SKill/Skill.h"
#include "Lightning.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API ALightning : public ASkill
{
	GENERATED_BODY()
public:
	ALightning();
	virtual void SkillExecute(class ATangTangCharacter* Character) override;

protected:
	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	void LightningSpawn();

	UPROPERTY()
	class ATangTangCharacter* TangTangCharacter;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* LightningParticle;

	UPROPERTY(VisibleAnywhere)
	int32 LightningSkillLevel = 0;
};
