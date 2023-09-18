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
	void SetSkill(class UTexture2D* Image,const FString& Name ,const FString& Text,const FString& Level );
	void SetSkill2(class UTexture2D* Image, const FString& Name, const FString& Text, const FString& Level);
	void SetSkill3(class UTexture2D* Image, const FString& Name, const FString& Text, const FString& Level);
	//void SkillInit();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USkillChooseWidget> SkillChooseWidgetClass;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess ="ture"))
	class USkillChooseWidget* SkillChooseWidget;

};
