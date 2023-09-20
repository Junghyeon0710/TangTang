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

	//캐릭터 상대적인 X거리
	UPROPERTY(EditAnywhere)
	float RadiusX =100.f;

	//캐릭터 상대적인 Y거리
	UPROPERTY(EditAnywhere)
	float RadiusY =100.f;
	
	//시작값
	UPROPERTY(EditAnywhere)
	float Time = 0.f;

	//공도는 스피드
	UPROPERTY(EditAnywhere)
	float Speed = 150;

	void AroundCharacter();

	FTimerHandle GuardianDamageTimer;

	//겹쳐있을때 1초에 몇번 뎀지 줄건지
	UPROPERTY(EditAnywhere)
	float GuardianDamageTiemDelay;

	void GuardianDamage();

	class IHitInterface* HitInterface;

};
