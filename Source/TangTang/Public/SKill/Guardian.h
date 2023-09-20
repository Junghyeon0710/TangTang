// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SKill/Skill.h"

#include "Guardian.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API AGuardian : public ASkill
{
	GENERATED_BODY()
public:
	AGuardian();
	virtual void Tick(float DeltaTime) override;
	virtual void SkillExecute(class ATangTangCharacter* Character) override;
protected:
	virtual void BeginPlay() override;

	virtual void SphereBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
private:
	UPROPERTY()
	class ATangTangCharacter* TangTangCharacter;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* GuardianRoot;

	//ĳ���� ������� X�Ÿ�
	UPROPERTY(EditAnywhere)
	float RadiusX =100.f;

	//ĳ���� ������� Y�Ÿ�
	UPROPERTY(EditAnywhere)
	float RadiusY =100.f;
	
	//���۰�
	UPROPERTY(EditAnywhere)
	float Time = 0.f;

	//������ ���ǵ�
	UPROPERTY(EditAnywhere)
	float Speed = 150;

	void AroundCharacter();

	FTimerHandle GuardianDamageTimer;

	//���������� 1�ʿ� ��� ���� �ٰ���
	UPROPERTY(EditAnywhere)
	float GuardianDamageTiemDelay;

	void GuardianDamage();

	class IHitInterface* HitInterface;

};
