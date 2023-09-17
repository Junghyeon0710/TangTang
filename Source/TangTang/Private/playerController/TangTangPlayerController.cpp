// Fill out your copyright notice in the Description page of Project Settings.


#include "playerController/TangTangPlayerController.h"
#include <HUD/SkillChooseWidget.h>
#include "Kismet/GameplayStatics.h"

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
