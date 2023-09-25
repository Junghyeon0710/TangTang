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
#include <SKill/Guardian.h>
#include <Components/BoxComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <SKill/Lightning.h>
#include <Kismet/GameplayStatics.h>
#include <Components/ArrowComponent.h>
#include <SKill/Tornado.h>
#include <Skill/Molotovcocktail.h>

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


	LightningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LightningBox"));
	LightningBox->SetupAttachment(RootComponent);

	/** 토네이도 */
	TornadoArrowComponent1 = CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent1"));
	TornadoArrowComponent1->SetupAttachment(RootComponent);

	TornadoArrowComponent2 = CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent2"));
	TornadoArrowComponent2->SetupAttachment(RootComponent);

	TornadoArrowComponent3 = CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent3"));
	TornadoArrowComponent3->SetupAttachment(RootComponent);

	TornadoArrowComponent4 = CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent4"));
	TornadoArrowComponent4->SetupAttachment(RootComponent);

	TornadoArrowComponent5 = CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent5"));
	TornadoArrowComponent5->SetupAttachment(RootComponent);

	TornadoArrowComponent.Add(TornadoArrowComponent1);
	TornadoArrowComponent.Add(TornadoArrowComponent2);
	TornadoArrowComponent.Add(TornadoArrowComponent3);
	TornadoArrowComponent.Add(TornadoArrowComponent4);
	TornadoArrowComponent.Add(TornadoArrowComponent5);

	/** 화염병 */
	MolotovococktailArrowComponent1 = CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent1"));
	MolotovococktailArrowComponent1->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent2 = CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent2"));
	MolotovococktailArrowComponent2->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent3 = CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent3"));
	MolotovococktailArrowComponent3->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent4 = CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent4"));
	MolotovococktailArrowComponent4->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent5 = CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent5"));
	MolotovococktailArrowComponent5->SetupAttachment(RootComponent);

	TornadoArrowComponent.Add(MolotovococktailArrowComponent1);
	TornadoArrowComponent.Add(MolotovococktailArrowComponent2);
	TornadoArrowComponent.Add(MolotovococktailArrowComponent3);
	TornadoArrowComponent.Add(MolotovococktailArrowComponent4);
	TornadoArrowComponent.Add(MolotovococktailArrowComponent5);


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
	if (PlayerExp >= PlayerMaxExp)
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

void ATangTangCharacter::GuardianSpawn()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->SpawnActor<AGuardian>(GuardianClass, GetActorTransform());
	}
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
	if(SkillNumber.Num()>0) SkillNumber.Empty();
		
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
	UE_LOG(LogTemp, Error, TEXT("index1 : %d index2 : %d , index3 : %d"),
		SkillNumber[0], SkillNumber[1], SkillNumber[2]);
}

void ATangTangCharacter::SpawnTornado()
{
	if (TornadoClass)
	{
		for (int32 i = 0; i < TornadoIndex; i++)
		{
			ATornado* Torando = GetWorld()->SpawnActor<ATornado>(TornadoClass, TornadoArrowComponent[i]->GetComponentTransform());
			if (Torando)
			{
				Torando->SetLifeSpan(5.f);
			}
			if (TornadoSound)
			{
				UGameplayStatics::PlaySound2D(this, TornadoSound);
			}
		}
	}
}

void ATangTangCharacter::SpawnTorandoTimer()
{
	GetWorldTimerManager().SetTimer(TornadoTimer, this, &ATangTangCharacter::SpawnTornado, 1 / TornadoDelay, true, 4.f);
}

void ATangTangCharacter::SpawnMolotovcoktail()
{
	if (MolotovcocktailClass)
	{
		for (int32 i = 0; i < MolotovcocktaillIndex; i++)
		{
			AMolotovcocktail* Molotovcocktail = GetWorld()->SpawnActor<AMolotovcocktail>(MolotovcocktailClass, TornadoArrowComponent[i]->GetComponentTransform());
			if (MolotovcocktailSound)
			{
				UGameplayStatics::PlaySound2D(this, TornadoSound);
			}
		}
	}
}

void ATangTangCharacter::SpawnMolotovcoktailTimer()
{
	GetWorldTimerManager().SetTimer(MolotovcocktailTimer, this, &ATangTangCharacter::SpawnMolotovcoktail, 1 / MolotovcocktailDelay, true, 4.f);

}


///////////////////////////////F///////////////////////////////////////////
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

void ATangTangCharacter::SpawnLightning()
{
	if (LightningClass)
	{
		for (int32 i = 0; i < LightningLevel; i++)
		{
			FVector LightningSpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(
				LightningBox->GetComponentLocation(), LightningBox->GetScaledBoxExtent()
			);
			ALightning* Lightning = GetWorld()->SpawnActor<ALightning>(LightningClass, FTransform(LightningSpawnPoint));
			if (Lightning) Lightning->SetLifeSpan(1.f);
			if (LightningSound)
			{
				UGameplayStatics::PlaySound2D(this, LightningSound);
			}
		}


	}
}

void ATangTangCharacter::SpawnLightningTimer()
{
	GetWorldTimerManager().SetTimer(
		LightningTimer,
		this,
		&ATangTangCharacter::SpawnLightning,
		1 / LightningTimeDelay,
		true, 5.f);
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

