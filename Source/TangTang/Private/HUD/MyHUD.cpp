// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyHUD.h"
#include <HUD/CharacterOverlay.h>
void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController && CharacterOverlayclass)
		{
			CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayclass);
			if (CharacterOverlay)
			{
				CharacterOverlay->AddToViewport();
			}
		}
	}

}
