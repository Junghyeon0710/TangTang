// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TangTangPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API ATangTangPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void CreateSkillWidget();
	void SetSkill1();
	void SetSkill2();
	void SetSkill3();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USkillChooseWidget> SkillChooseWidgetClass;

	UPROPERTY()
	class USkillChooseWidget* SkillChooseWidget;

};
