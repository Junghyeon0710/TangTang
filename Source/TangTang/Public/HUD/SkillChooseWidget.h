// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillChooseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANGTANG_API USkillChooseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** 스킬 1 UI*/
	UPROPERTY(meta = (BindWidget))
	class UImage* Skill1Image;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill1Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill1Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill1Level;

	UPROPERTY(meta = (BindWidget))
	class UButton* Skill1Button;

	/** 스킬 2 UI*/
	UPROPERTY(meta = (BindWidget))
	class UImage* Skill2Image;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill2Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill2Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill2Level;

	UPROPERTY(meta = (BindWidget))
	class UButton* Skill2Button;

	/** 스킬3 UI*/
	UPROPERTY(meta = (BindWidget))
	class UImage* Skill3Image;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill3Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill3Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Skill3Level;

	UPROPERTY(meta = (BindWidget))
	class UButton* Skill3Button;

};
