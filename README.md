## Unreal5 : RunGame
포트폴리오 목적으로 제작된 간단한 런게임입니다.

- 엔진 : Unreal Engine 5.3
- IDE : Visual Studio 2022
- 툴 : C++ , Blueprint 혼합사용
- 인원 : 개인 개발

## 영상
[![Video Label](https://img.youtube.com/vi/JK8cCLz8lUc/0.jpg)](https://www.youtube.com/watch?v=JK8cCLz8lUc')



## 기술 설명
### Character
- Skill Spawn(갖고 있는 스킬을 스폰)
- Skill Timer(갖고 있는 스킬을 타이머로 관리)
- Skill Info(스킬 정보를 관리함)
- Level(레벨 및 경험치 관리)
- GetDamage(적한테 데미지를 입을 시)

#### ArrowComponent를 캐릭터에 붙여 스킬 시작위치를 지정하는 방식을 사용하거나 각 스킬 함수를 통해 구현했습니다.
![캡처](https://github.com/Junghyeon0710/TangTang/assets/133496610/53d67aa4-1a3a-4c64-82dd-4ece66c2cabd)


>Skill Info
### 레벨업을 할 시 선택할 수 있는 스킬 3개를 보여줘야하는데 어떻게 할지 고민하다가 스킬을 배열에 담아 랜덤으로 인덱스 값을 가져오는 방식으로 했습니다.
```C++
void ATangTangCharacter::Skill1Info()
{
	if (TangTangPlayerController && CharacterSkill.Num() > 0)
	{
		SkillNumber.Empty(); //비워줌

		while (SkillNumber.Num() < 3)
		{
			const int32 SkillIndex = FMath::RandRange(0, CharacterSkill.Num() - 1); //0에서 가지고있는 스킬만큼 랜덤인덱스 가지고 옴
			SkillNumber.AddUnique(SkillIndex); // 인덱스가 겹치지 않게 AddUnique를 사용
		}

		for (int32 i = 0; i < SkillNumber.Num(); i++)
		{
			const int32 SelectedSkillIndex = SkillNumber[i]; //랜덤으로 가져온 인덱스를 가져옴 
			const ASkill* SelectedSkill = CharacterSkill[SelectedSkillIndex].GetDefaultObject(); //해당 인덱스 스킬정보를 가져옴

			if (SelectedSkill)
			{
				TangTangPlayerController->SetSkill(
					SelectedSkill->GetSkillImage(),
					SelectedSkill->GetSkillName(),
					SelectedSkill->GetSkillText(),
					SelectedSkill->GetSkillLevel(),
          i
				);
			}
		}
	}
}
```

>레벨업
### 레벨업은 간단하게 경험치바를 2배로 올려주는 방식을 설정했습니다. 이렇게 하는 대신 적의 경험치는 점점 높아져야 할 것을 의미합니다..
```C++
void ATangTangCharacter::LevelUp()
{
	PlayerLevel++;
	PlayerExp = 0;
	PlayerMaxExp *= 2;
	UpdateHUDExpBar();

	if (TangTangPlayerController)
	{
		TangTangPlayerController->CreateSkillWidget();
		Skill1Info();
	}
}
```

## Weapon
- Attach weapon(무기를 붙여줌)
- SpawnProjectile(총알을 발사)

>Weapon Blueprint
#### ArrowComponet를 이용하여 블루프린트로 총알 위치를 원하는 위치로 구현할 수 있게 했습니다. 이렇게 하면 코드를 몰라도 위치를 지정할 수 있습니다.
![캡처](https://github.com/Junghyeon0710/TangTang/assets/133496610/8bb4eb84-e2cc-4c0d-b23f-7a0aa13079ea)
#### ArrowComponet를 사용함으로써 방향을 알 수 있습니다.

## Skill
#### 스킬이 가지고 있어야 변수와 함수를 갖고 있는 스킬 부모 클래스


