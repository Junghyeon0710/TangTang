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
	void HUDHealth(float GetHealth);
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ASkill>> CharacterSkill;

	TArray<int32> SkillNumber;
	void SpawnLightning();
	void SpawnLightningTimer();
	void SpawnTornado();
	void SpawnTorandoTimer();
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
	uint32 PlayerLevel = 1;

	/** 플레이 시간*/
	float Time = 0.f;

	/** 플레이어 HUD*/
	UPROPERTY()
	class AMyHUD* MyHUD;

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;


	void WorldTime();
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

	/** 번개 스킬*/

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* LightningBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALightning> LightningClass;

	FTimerHandle LightningTimer;

	UPROPERTY(EditAnywhere)
	float LightningTimeDelay = .5f;

	UPROPERTY(VisibleAnywhere)
	int32 LightningLevel = 0;

	UPROPERTY(EditAnywhere)
	class USoundBase* LightningSound;

	UPROPERTY(VisibleAnywhere)
	TArray<class UArrowComponent*> TornadoArrowComponent;

	/** 토네이토 스킬*/
	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* TornadoArrowComponent1;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* TornadoArrowComponent2;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* TornadoArrowComponent3;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* TornadoArrowComponent4;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* TornadoArrowComponent5;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATornado> TornadoClass;

	UPROPERTY(EditAnywhere)
	int32 TornadoIndex = 0;

	FTimerHandle TornadoTimer;

	UPROPERTY(EditAnywhere)
	float TornadoDelay = 0.25;

	UPROPERTY(EditAnywhere)
	class USoundBase* TornadoSound;

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
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float GetHealth) { Health = GetHealth; }
	FORCEINLINE float GetMaxHelath() const { return MaxHealth; }
	FORCEINLINE void SetMaxHealth(float GetMaxHealth) { MaxHealth = GetMaxHealth; }
	FORCEINLINE int32 GetLightningLevel() const { return LightningLevel; }
	FORCEINLINE void SetLightningLevel(int32 Level) { LightningLevel = Level; }
	FORCEINLINE int32 GetTornadoIndex() const { return TornadoIndex; }
	FORCEINLINE void SetTornadoIndex(int32 Index) { TornadoIndex = Index; }
};

