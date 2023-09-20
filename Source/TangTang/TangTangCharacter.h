// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InputActionValue.h"
#include "TangTangCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UENUM(BlueprintType)
enum class ESkillName : uint8
{
	ESN_Guardian UMETA(Display = "Guardian"),
	ESN_ProjectilePlus UMETA(Display = "ProjectilePlus"),
	ESN_ProjectileSpeedUp UMETA(Display = "ProjectileSpeedUp"),

	ESN_Max UMETA(Display = "Max"),
};

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
	void GuardianSpawn();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ASkill>> CharacterSkill;

	TArray<int32> SkillNumber;
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
private:
	/** �ÿ��̾� ü��*/
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float Health = 100.f;

	/** �÷��̾� ����ġ & ����*/
	UPROPERTY(EditAnywhere)
	float PlayerMaxExp = 100;

	UPROPERTY(EditAnywhere)
	float PlayerExp = 0;

	UPROPERTY(EditAnywhere)
	uint32 PlayerLevel = 1;

	/** �÷��� �ð�*/
	float Time = 0.f;

	/** �÷��̾� HUD*/
	UPROPERTY()
	class AMyHUD* MyHUD;

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;


	void WorldTime();
	void HUDHealth(float GetHealth);
	void Die();
	void HUDExp(float GetExp);
	void Skill1Info();

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess = "true"))
	bool EnemyOverlap = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "ture"))
	int32 OverlapNum;

	UPROPERTY()
	class ATangTangPlayerController* TangTangPlayerController;

	class UTexture2D* CharacterSkillImage;
	FString CharacterSkillName;
	FString CharacterSkillText;

	ESkillName SkillName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGuardian> GuardianClass;

	UPROPERTY()
	class AWeapon* CharacterWeapon;

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
	FORCEINLINE AWeapon* GetCharacterWeapon() const { return CharacterWeapon; }
	FORCEINLINE void SetCharacterWeapon(class AWeapon* Weapon) { CharacterWeapon = Weapon; }

};
