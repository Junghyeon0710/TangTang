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

	/** ���� */
	virtual void GetDamage(float Damage);
	virtual void GetExp(float Exp);
	void HUDHealth(float GetHealth);

	/** ��ų ����*/
	void SpawnLightning();
	void SpawnLightningTimer();
	void SpawnTornado();
	void SpawnTornadoTimer();
	void SpawnMolotovcoktail();
	void SpawnMolotovcoktailTimer();
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
	/** �Է� */
	void SetupInputMappingContext();

	/** ���� */
	void InitializeHUD();
	void WorldTime();
	void Die();
	void HUDExp(float GetExp);
	void Skill1Info();
	void LevelUp();
	void UpdateHUDExpBar();

	UPROPERTY()
	class ATangTangPlayerController* TangTangPlayerController;

	UPROPERTY()
    class AWeapon* CharacterWeapon;

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

	/** ���� ��� */
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess = "true"))
	bool bEnemyOverlap = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "ture"))
	int32 OverlapNum;

	/** ��ų */
	class UTexture2D* CharacterSkillImage;
	FString CharacterSkillName;
	FString CharacterSkillText;

	/** ��ȣ�� ��ų */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGuardian> GuardianClass;

	/** ���� ��ų*/
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
	/*/���� ��ų*/


	/** ������� ��ų*/
	UPROPERTY(VisibleAnywhere)
	TArray<class UArrowComponent*> TornadoArrowComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATornado> TornadoClass;

	UPROPERTY(EditAnywhere)
	int32 TornadoIndex = 0;

	FTimerHandle TornadoTimer;

	UPROPERTY(EditAnywhere)
	float TornadoDelay = 0.25;

	UPROPERTY(EditAnywhere)
	class USoundBase* TornadoSound;
	/** /������� ��ų*/

	/** ȭ���� ��ų*/
	UPROPERTY(VisibleAnywhere)
	TArray<class UArrowComponent*> MolotovococktailArrowComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMolotovcocktail> MolotovcocktailClass;

	UPROPERTY(EditAnywhere)
	int32 MolotovcocktaillIndex = 0;

	FTimerHandle MolotovcocktailTimer;

	UPROPERTY(EditAnywhere)
	float MolotovcocktailDelay = 0.18;

	UPROPERTY(EditAnywhere)
	class USoundBase* MolotovcocktailSound;
	/** /ȭ���� ��ų*/

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool IsEnemyOverlapping() const { return bEnemyOverlap; }
	FORCEINLINE void SetIsEnemyOverlap(bool Overlap) { bEnemyOverlap = Overlap; }

	FORCEINLINE int32 GetOverlapNum() const { return OverlapNum; }
	FORCEINLINE float GetPlayerMaxExp() const { return PlayerMaxExp; }
	FORCEINLINE float GetPlayerExp() const { return PlayerExp; }
	FORCEINLINE void SetPlayerExp(float Exp) { PlayerExp = Exp; }
	FORCEINLINE int32 GetPalyerLevel() const { return PlayerLevel; }
	FORCEINLINE void SetPlayerLevel(int32 Level) { PlayerLevel = Level; }
	FORCEINLINE AWeapon* GetCharacterWeapon() const { return CharacterWeapon; }
	FORCEINLINE void SetCharacterWeapon(class AWeapon* Weapon) { CharacterWeapon = Weapon; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float GetHealth) { Health = GetHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE void SetMaxHealth(float GetMaxHealth) { MaxHealth = GetMaxHealth; }
	
	FORCEINLINE void IncreaseLightningLevel() { LightningLevel++; };
	FORCEINLINE void IncreaseMolotovcocktailIndex() { MolotovcocktaillIndex++; }
	FORCEINLINE void IncreaseTornadoIndex() { TornadoIndex++; }
	FORCEINLINE void IncreaseOverlapNum() { OverlapNum++; }
	FORCEINLINE void DecreaseOverlapNum() { OverlapNum--; }
	
};

