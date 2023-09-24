// Fill out your copyright notice in the Description page of Project Settings.


#include "playerController/TangTangPlayerController.h"
#include <HUD/SkillChooseWidget.h>
#include "Kismet/GameplayStatics.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <TangTang/TangTangCharacter.h>
#include <SKill/Skill.h>
#include <SKill/Guardian.h>

void ATangTangPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void ATangTangPlayerController::CreateSkillWidget()
{
	if (SkillChooseWidgetClass)
	{
		SkillChooseWidget = CreateWidget<USkillChooseWidget>(this, SkillChooseWidgetClass);
		if (SkillChooseWidget)
		{
			SkillChooseWidget->AddToViewport();

			UGameplayStatics::SetGamePaused(this,true);
			FInputModeUIOnly InputModeUIOnly;
			InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputModeUIOnly.SetWidgetToFocus(SkillChooseWidget->GetCachedWidget());
			SetInputMode(InputModeUIOnly);
			bShowMouseCursor = true;

			SkillChooseWidget->Skill1Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::Skill1ButtonClick);
			SkillChooseWidget->Skill2Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::Skill2ButtonClick);
			SkillChooseWidget->Skill3Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::Skill3ButtonClick);
		}
	}
}

void ATangTangPlayerController::SetSkill(UTexture2D* Image, const FString& Name, const FString& Text,const FString& Level)
{
	if (SkillChooseWidget)
	{
		SkillChooseWidget->Skill1Image->SetBrushFromTexture(Image);
		SkillChooseWidget->Skill1Name->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Name)));
		SkillChooseWidget->Skill1Text->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Text)));
		SkillChooseWidget->Skill1Level->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Level)));
	}
}

void ATangTangPlayerController::SetSkill2(UTexture2D* Image, const FString& Name, const FString& Text, const FString& Level)
{
	if (SkillChooseWidget)
	{
		SkillChooseWidget->Skill2Image->SetBrushFromTexture(Image);
		SkillChooseWidget->Skill2Name->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Name)));
		SkillChooseWidget->Skill2Text->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Text)));
		SkillChooseWidget->Skill2Level->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Level)));
	}
}

void ATangTangPlayerController::SetSkill3(UTexture2D* Image, const FString& Name, const FString& Text, const FString& Level)
{
	if (SkillChooseWidget)
	{
		SkillChooseWidget->Skill3Image->SetBrushFromTexture(Image);
		SkillChooseWidget->Skill3Name->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Name)));
		SkillChooseWidget->Skill3Text->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Text)));
		SkillChooseWidget->Skill3Level ->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Level)));

	}
}

void ATangTangPlayerController::Skill1ButtonClick()
{
	if (SkillChooseWidget) SkillChooseWidget->RemoveFromParent();
	UGameplayStatics::SetGamePaused(this,false);
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	TangTangCharacter = TangTangCharacter == nullptr ?
		Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))
		: TangTangCharacter;
	bShowMouseCursor = false;
	if (TangTangCharacter)
	{
		TangTangCharacter->CharacterSkill
			[TangTangCharacter->SkillNumber[0]].
			GetDefaultObject()->SkillExecute(TangTangCharacter);
	}

}

void ATangTangPlayerController::Skill2ButtonClick()
{
	if (SkillChooseWidget) SkillChooseWidget->RemoveFromParent();
	UGameplayStatics::SetGamePaused(this, false);
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	TangTangCharacter = TangTangCharacter == nullptr ?
		Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))
		: TangTangCharacter;
	bShowMouseCursor = false;
	if (TangTangCharacter)
	{
		TangTangCharacter->CharacterSkill
			[TangTangCharacter->SkillNumber[1]].
			GetDefaultObject()->SkillExecute(TangTangCharacter);	
	}
	
}

void ATangTangPlayerController::Skill3ButtonClick()
{
	if (SkillChooseWidget) SkillChooseWidget->RemoveFromParent();
	UGameplayStatics::SetGamePaused(this, false);
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	TangTangCharacter = TangTangCharacter == nullptr ?
		Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))
		: TangTangCharacter;
	bShowMouseCursor = false;
	if (TangTangCharacter)
	{
		TangTangCharacter->CharacterSkill
			[TangTangCharacter->SkillNumber[2]].
			GetDefaultObject()->SkillExecute(TangTangCharacter);
	}

}



