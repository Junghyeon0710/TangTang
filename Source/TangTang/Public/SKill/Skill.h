// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Skill.generated.h"

UCLASS()
class TANGTANG_API ASkill : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkill();
	virtual void SkillExecute(class ATangTangCharacter* Character);
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SkillMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereOverlap;

	/** ��ų �̹��� */
	UPROPERTY(EditAnywhere,Category = SKill)
	class UTexture2D* SkillImage;

	/** ��ų �̸� */
	UPROPERTY(EditAnywhere, Category = SKill)
	FString SkillName;

	/** ��ų ���� */
	UPROPERTY(EditAnywhere, Category = SKill)
	FString SkillText;

	/** ��ų ���� */
	UPROPERTY(EditAnywhere, Category = SKill)
	FString SkillLevel;

	/** ��ų ������ */
	UPROPERTY(EditAnywhere, Category = SKill)
	float SkillDamage = 10.f;

	UPROPERTY(EditAnywhere)
	class USoundBase* SkillExecuteSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* SkillOverlapSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SkillOverlapParticle;

/** �ζ����Լ� Get/Set */
public:	
	
	FORCEINLINE class UTexture2D* GetSkillImage() const { return SkillImage;}
	FORCEINLINE FString GetSkillName() const { return SkillName; }
	FORCEINLINE FString GetSkillText() const { return SkillText; }
	FORCEINLINE FString GetSkillLevel() const { return SkillLevel; }
};
