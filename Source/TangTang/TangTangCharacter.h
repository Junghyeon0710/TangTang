// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "TangTangCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATangTangCharacter : public ACharacter 
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;


public:
	ATangTangCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void GetDamage(float Damage);
	virtual void GetExp(float Exp);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
private:
	/** 플에이어 체력*/
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float Health = 100.f;

	/** 플레이어 경험치 & 레벨*/
	UPROPERTY(EditAnywhere)
	float PlayerMaxExp = 100;

	UPROPERTY(EditAnywhere)
	float PlayerExp = 0;

	UPROPERTY(EditAnywhere)
	uint32 PlayerLevel = 0;

	/** 플레이 시간*/
	float Time = 0.f;

	/** 플레이어 HUD*/
	UPROPERTY()
	class AMyHUD* MyHUD;

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;


	void WorldTime();
	void HUDHealth(float GetHealth);
	void Die();
	void HUDExp(float GetExp);

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess = "true"))
	bool EnemyOverlap = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "ture"))
	int32 OverlapNum;

	UPROPERTY()
	class ATangTangPlayerController* TangTangPlayerController;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ASkill>> CharacterSkill;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetEnemyOverlap() const { return EnemyOverlap; }
	FORCEINLINE void SetEnemyOverlap(bool Overlap) { EnemyOverlap = Overlap; }
	FORCEINLINE int32 GetOverlapNum() const { return OverlapNum; }
	FORCEINLINE void SetOverlapNum(int32 Num)  {  OverlapNum = Num; }
	FORCEINLINE float GetPlayerMaxExp() const { return PlayerMaxExp; }
	FORCEINLINE float GetPlayerExp() const { return PlayerExp; }
	FORCEINLINE void SetPlayerExp(float Exp) { PlayerExp = Exp; }
	FORCEINLINE int32 GetPalyerLevel() const { return PlayerLevel; }
	FORCEINLINE void SetPlayerLevel(int32 Level) { PlayerLevel = Level; }
};

