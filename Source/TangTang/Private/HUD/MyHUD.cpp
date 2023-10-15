// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyHUD.h"
#include <HUD/CharacterOverlay.h>

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && CharacterOverlayClass)
    {
        // CharacterOverlay Ŭ������ ���� �ν��Ͻ� ����
        CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
        if (CharacterOverlay)
        {
            // ȭ�鿡 ���� �߰�
            CharacterOverlay->AddToViewport();
        }
    }
}
