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
			FOnButtonClickedEvent OnButtonClickedEvent;
			
			SkillChooseWidget->Skill1Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::OnSkill1ButtonClick);
			SkillChooseWidget->Skill2Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::OnSkill2ButtonClick);
			SkillChooseWidget->Skill3Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::OnSkill3ButtonClick);
		}
	}
}

void ATangTangPlayerController::SetSkill(UTexture2D* Image, const FString& Name, const FString& Text,const FString& Level,const int32& SkillSlot)
{
	if (SkillChooseWidget && SkillSlot >= 0 && SkillSlot < 3)
	{
		if (SkillSlot == 0)
		{
			SkillChooseWidget->Skill1Image->SetBrushFromTexture(Image);
			SkillChooseWidget->Skill1Name->SetText(FText::FromString(Name));
			SkillChooseWidget->Skill1Text->SetText(FText::FromString(Text));
			SkillChooseWidget->Skill1Level->SetText(FText::FromString(Level));
		}
		else if (SkillSlot == 1)
		{
			SkillChooseWidget->Skill2Image->SetBrushFromTexture(Image);
			SkillChooseWidget->Skill2Name->SetText(FText::FromString(Name));
			SkillChooseWidget->Skill2Text->SetText(FText::FromString(Text));
			SkillChooseWidget->Skill2Level->SetText(FText::FromString(Level));
		}
		else if (SkillSlot == 2)
		{
			SkillChooseWidget->Skill3Image->SetBrushFromTexture(Image);
			SkillChooseWidget->Skill3Name->SetText(FText::FromString(Name));
			SkillChooseWidget->Skill3Text->SetText(FText::FromString(Text));
			SkillChooseWidget->Skill3Level->SetText(FText::FromString(Level));
		}
	}
}



void ATangTangPlayerController::OnSkill1ButtonClick()
{
	WhatSkillButtonClick(0);
}

void ATangTangPlayerController::OnSkill2ButtonClick()
{
	WhatSkillButtonClick(1);
}

void ATangTangPlayerController::OnSkill3ButtonClick()
{
	WhatSkillButtonClick(2);
}

void ATangTangPlayerController::WhatSkillButtonClick(const int32& SkillSlot)
{
	if (SkillChooseWidget == nullptr || SkillSlot < 0 || SkillSlot >= 3) return;

	TangTangCharacter = TangTangCharacter ? TangTangCharacter : Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (TangTangCharacter)
	{
		SkillChooseWidget->RemoveFromParent();
		bShowMouseCursor = false;
		TangTangCharacter->CharacterSkill[TangTangCharacter->SkillNumber[SkillSlot]].GetDefaultObject()->SkillExecute(TangTangCharacter);
		UGameplayStatics::SetGamePaused(this, false);
		FInputModeGameAndUI InputMode;
		SetInputMode(InputMode);
	}
}