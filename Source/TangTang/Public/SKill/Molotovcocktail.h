// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SKill/Skill.h"
#include "Molotovcocktail.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AMolotovcocktail : public ASkill
{
	GENERATED_BODY()
public:
	AMolotovcocktail();
	virtual void SkillExecute(class ATangTangCharacter* Character) override;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
private:

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* FireParticle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpawnFire> SpawnFireClass;

	UPROPERTY(EditAnywhere)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* SpawnFireSound;
};
