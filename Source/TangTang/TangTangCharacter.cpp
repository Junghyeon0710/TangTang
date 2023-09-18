// Copyright Epic Games, Inc. All Rights Reserved.

#include "TangTangCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <HUD/MyHUD.h>
#include <playerController/TangTangPlayerController.h>
#include <HUD/CharacterOverlay.h>
#include <SKill/Skill.h>


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATangTangCharacter

ATangTangCharacter::ATangTangCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 700.f);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetWorldRotation(FRotator(0.f,-90.f,0.f));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATangTangCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WorldTime();
}

void ATangTangCharacter::GetDamage(float Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		Die();
	}

	HUDHealth(Health / MaxHealth);
}

void ATangTangCharacter::GetExp(float Exp)
{
	PlayerExp += Exp;
	if (PlayerExp >= 100)
	{
		PlayerLevel++;
		PlayerExp = 0;
		PlayerMaxExp *= PlayerLevel;
		HUDExp(0.f);
		if (TangTangPlayerController)
		{
			TangTangPlayerController->CreateSkillWidget();	
			Skill1Info();
		}
		return;
	}
	
	HUDExp(PlayerExp / PlayerMaxExp);
}

void ATangTangCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	TangTangPlayerController = Cast<ATangTangPlayerController>(GetController());
	if (TangTangPlayerController)
	{
		MyHUD = Cast<AMyHUD>(TangTangPlayerController->GetHUD());
		if (MyHUD)
		{
			CharacterOverlay = MyHUD->GetCharacterOverlay();
			if (CharacterOverlay)
			{
				CharacterOverlay->SetTime(0.f);
				CharacterOverlay->SetHealthBar(100.f);
				CharacterOverlay->SetExpBar(0.f);
			}
		}
	}
}

void ATangTangCharacter::WorldTime()
{
	if (CharacterOverlay)
	{
		CharacterOverlay->SetTime(Time += GetWorld()->GetDeltaSeconds());
	}

}

void ATangTangCharacter::HUDHealth(float GetHealth)
{
	if (CharacterOverlay)
	{
		CharacterOverlay->SetHealthBar(GetHealth);
	}
}

void ATangTangCharacter::Die()
{
	Destroy();
}

void ATangTangCharacter::HUDExp(float GetExp)
{
	if (CharacterOverlay)
	{
		CharacterOverlay->SetExpBar(GetExp);
	}
}

void ATangTangCharacter::Skill1Info()
{
	if (TangTangPlayerController == nullptr) return;
	if (CharacterSkill.Num() < 0) return;
	TArray<int32> SkillNumber;
	for (int32 i = 0; i < 100; i++)
	{
		const int32 SkillIndex = FMath::RandRange(0, CharacterSkill.Num() - 1);
		SkillNumber.AddUnique(SkillIndex);
		if (SkillNumber.Num() == 3) break;
	}
	if (CharacterSkill[SkillNumber[0]].GetDefaultObject())
	{
		TangTangPlayerController->SetSkill(
			CharacterSkill[SkillNumber[0]].GetDefaultObject()->GetSkillImage(),
			CharacterSkill[SkillNumber[0]].GetDefaultObject()->GetSkillName(),
			CharacterSkill[SkillNumber[0]].GetDefaultObject()->GetSkillText(),
			CharacterSkill[SkillNumber[0]].GetDefaultObject()->GetSkillLevel());
	}
	if (CharacterSkill[SkillNumber[1]].GetDefaultObject())
	{
		TangTangPlayerController->SetSkill2(
			CharacterSkill[SkillNumber[1]].GetDefaultObject()->GetSkillImage(),
			CharacterSkill[SkillNumber[1]].GetDefaultObject()->GetSkillName(),
			CharacterSkill[SkillNumber[1]].GetDefaultObject()->GetSkillText(),
			CharacterSkill[SkillNumber[1]].GetDefaultObject()->GetSkillLevel());
	}
	if (CharacterSkill[SkillNumber[2]].GetDefaultObject())
	{
		TangTangPlayerController->SetSkill3(
			CharacterSkill[SkillNumber[2]].GetDefaultObject()->GetSkillImage(),
			CharacterSkill[SkillNumber[2]].GetDefaultObject()->GetSkillName(),
			CharacterSkill[SkillNumber[2]].GetDefaultObject()->GetSkillText(),
			CharacterSkill[SkillNumber[2]].GetDefaultObject()->GetSkillLevel());
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void ATangTangCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATangTangCharacter::Move);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATangTangCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

