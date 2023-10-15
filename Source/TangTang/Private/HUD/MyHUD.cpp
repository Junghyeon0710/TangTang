// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyHUD.h"
#include <HUD/CharacterOverlay.h>

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && CharacterOverlayClass)
    {
        // CharacterOverlay 클래스로 위젯 인스턴스 생성
        CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
        if (CharacterOverlay)
        {
            // 화면에 위젯 추가
            CharacterOverlay->AddToViewport();
        }
    }
}
