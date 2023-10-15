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
	virtual void SphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	// Guardian ��ų ������ �Լ�
	void GuardianDamage();

	// ĳ���� ������ ���� �Լ�
	void UpdateGuardianLocation();

	// ĳ���� ���� ����
	UPROPERTY()
	class ATangTangCharacter* TangTangCharacter;

	// Guardian ��Ʈ ������Ʈ
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* GuardianRoot;

	// Guardian ��ų�� ������ (X, Y)
	UPROPERTY(EditAnywhere)
	float GuardianRadiusX = 100.f;
	UPROPERTY(EditAnywhere)
	float GuardianRadiusY = 100.f;

	// Guardian ��ų �ð� �� �ӵ�
	UPROPERTY(EditAnywhere)
	float GuardianTime = 0.f;
	UPROPERTY(EditAnywhere)
	float GuardianSpeed = 150;

	// �ֺ��� ������ �ֱ������� �������� ������ Ÿ�̸� ���� ����
	FTimerHandle GuardianDamageTimer;

	// �������� �� 1�ʿ� �� �� �������� �ִ����� ���� ������ �ð�
	UPROPERTY(EditAnywhere)
	float GuardianDamageTimeDelay = 1.0f;

	class IHitInterface* HitInterface;
};
