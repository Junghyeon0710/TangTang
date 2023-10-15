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
	// Guardian 스킬 데미지 함수
	void GuardianDamage();

	// 캐릭터 주위를 도는 함수
	void UpdateGuardianLocation();

	// 캐릭터 관련 변수
	UPROPERTY()
	class ATangTangCharacter* TangTangCharacter;

	// Guardian 루트 컴포넌트
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* GuardianRoot;

	// Guardian 스킬의 반지름 (X, Y)
	UPROPERTY(EditAnywhere)
	float GuardianRadiusX = 100.f;
	UPROPERTY(EditAnywhere)
	float GuardianRadiusY = 100.f;

	// Guardian 스킬 시간 및 속도
	UPROPERTY(EditAnywhere)
	float GuardianTime = 0.f;
	UPROPERTY(EditAnywhere)
	float GuardianSpeed = 150;

	// 주변의 적에게 주기적으로 데미지를 입히는 타이머 관련 변수
	FTimerHandle GuardianDamageTimer;

	// 겹쳐있을 때 1초에 몇 번 데미지를 주는지에 대한 딜레이 시간
	UPROPERTY(EditAnywhere)
	float GuardianDamageTimeDelay = 1.0f;

	class IHitInterface* HitInterface;
};
