// Copyright Epic Games, Inc. All Rights Reserved.

#include "TangTangCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include <Components/BoxComponent.h>
#include <Components/ArrowComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <playerController/TangTangPlayerController.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <HUD/MyHUD.h>
#include <HUD/CharacterOverlay.h>
#include <SKill/Skill.h>
#include <SKill/Guardian.h>
#include <SKill/Tornado.h>
#include <Skill/Molotovcocktail.h>
#include <SKill/Lightning.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATangTangCharacter

ATangTangCharacter::ATangTangCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 캡슐의 크기 설정
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// 컨트롤러가 회전할 때 캐릭터를 회전시키지 않도록 설정. 이는 카메라에만 영향을 미침
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터 이동 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// 카메라 생성 (충돌 시 플레이어에게 끌어당김)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true; 
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 700.f);

	// 팔로우 카메라 생성
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
	FollowCamera->SetWorldRotation(FRotator(0.f,-90.f,0.f));

	LightningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LightningBox"));
	LightningBox->SetupAttachment(RootComponent);

	/** 토네이도 */
	TornadoArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent1")));
	TornadoArrowComponent[0]->SetupAttachment(RootComponent);

	TornadoArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent2")));
	TornadoArrowComponent[1]->SetupAttachment(RootComponent);

	TornadoArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent3")));
	TornadoArrowComponent[2]->SetupAttachment(RootComponent);

	TornadoArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent4")));
	TornadoArrowComponent[3]->SetupAttachment(RootComponent);
	
	TornadoArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("TornadoArrowComponent5")));
	TornadoArrowComponent[4]->SetupAttachment(RootComponent);

	/** 화염병 */
	MolotovococktailArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent1")));
	MolotovococktailArrowComponent[0]->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent2")));
	MolotovococktailArrowComponent[1]->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent3")));
	MolotovococktailArrowComponent[2]->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent4")));
	MolotovococktailArrowComponent[3]->SetupAttachment(RootComponent);

	MolotovococktailArrowComponent.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("MolotovococktailArrowComponent5")));
	MolotovococktailArrowComponent[4]->SetupAttachment(RootComponent);

}

void ATangTangCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WorldTime();
}

void ATangTangCharacter::GetDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage,0,MaxHealth);
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
		LevelUp();
	}
	else
	{
		UpdateHUDExpBar();
	}
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
	Super::BeginPlay();

	SetupInputMappingContext();
	InitializeHUD();
}

void ATangTangCharacter::SetupInputMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void ATangTangCharacter::InitializeHUD()
{
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
	if(MyHUD)
	{
		MyHUD->GetCharacterOverlay()->RemoveFromParent();
	}
	TangTangPlayerController->bShowMouseCursor = true;
	CreateWidget(GetWorld(), DiewWidgetClass)->AddToViewport();
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
	if (TangTangPlayerController && CharacterSkill.Num() > 0)
	{
		SkillNumber.Empty();

		while (SkillNumber.Num() < 3)
		{
			const int32 SkillIndex = FMath::RandRange(0, CharacterSkill.Num() - 1);
			SkillNumber.AddUnique(SkillIndex);
		}

		for (int32 i = 0; i < SkillNumber.Num(); i++)
		{
			const int32 SelectedSkillIndex = SkillNumber[i];
			const ASkill* SelectedSkill = CharacterSkill[SelectedSkillIndex].GetDefaultObject();

			if (SelectedSkill)
			{
				TangTangPlayerController->SetSkill(
					SelectedSkill->GetSkillImage(),
					SelectedSkill->GetSkillName(),
					SelectedSkill->GetSkillText(),
					SelectedSkill->GetSkillLevel(),
					i
				);
			}
		}
	}
}

void ATangTangCharacter::LevelUp()
{
	PlayerLevel++;
	PlayerExp = 0;
	PlayerMaxExp *= PlayerLevel;
	UpdateHUDExpBar();

	if (TangTangPlayerController)
	{
		TangTangPlayerController->CreateSkillWidget();
		Skill1Info();
	}
}

void ATangTangCharacter::UpdateHUDExpBar()
{
	float ExpRatio = PlayerExp / PlayerMaxExp;
	HUDExp(ExpRatio);
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

void ATangTangCharacter::SpawnTornadoTimer()
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

void ATangTangCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{	
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATangTangCharacter::Move);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATangTangCharacter::SpawnLightning()
{
	if (!LightningClass || LightningLevel <= 0)
	{
		return;
	}

	for (int32 i = 0; i < LightningLevel; i++)
	{
		if (LightningBox)
		{
			FVector LightningSpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(
				LightningBox->GetComponentLocation(), LightningBox->GetScaledBoxExtent()
			);

			ALightning* Lightning = GetWorld()->SpawnActor<ALightning>(LightningClass, FTransform(LightningSpawnPoint));
			if (Lightning)
			{
				Lightning->SetLifeSpan(1.f);
			}
		}

		if (LightningSound)
		{
			UGameplayStatics::PlaySound2D(this, LightningSound);
		}
	}
}

void ATangTangCharacter::SpawnLightningTimer()
{
	GetWorldTimerManager().SetTimer(LightningTimer,	this,&ATangTangCharacter::SpawnLightning, 1 / LightningTimeDelay,true, 5.f);
}

void ATangTangCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

