// Fill out your copyright notice in the Description page of Project Settings.


#include "playerController/TangTangPlayerController.h"
#include <HUD/SkillChooseWidget.h>
#include "Kismet/GameplayStatics.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

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


