// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TangTangPlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkillButtonDelegate);

UCLASS()
class TANGTANG_API ATangTangPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void CreateSkillWidget();
	void SetSkill(class UTexture2D* Image,const FString& Name ,const FString& Text,const FString& Level,const int32& SkillSlot );
	
	void WhatSkillButtonClick(const int32& SkillSlot);

	UFUNCTION()
	void OnSkill1ButtonClick();

	UFUNCTION()
	void OnSkill2ButtonClick();
	
	UFUNCTION()
	void OnSkill3ButtonClick();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USkillChooseWidget> SkillChooseWidgetClass;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess ="ture"))
	class USkillChooseWidget* SkillChooseWidget;

	UPROPERTY()
	class ATangTangCharacter* TangTangCharacter;
};
