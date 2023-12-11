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
- Skill Timer(갖고 있는 스킬을 타이머로 스폰 시간 관리)
- Skill Info(스킬 정보를 관리함)
- Level(레벨 및 경험치 관리)
- GetDamage(적한테 데미지를 입을 시)

##### ArrowComponent를 캐릭터에 붙여 스킬 시작위치를 지정하는 방식을 사용하거나 각 스킬 함수를 통해 구현했습니다.
![캡처](https://github.com/Junghyeon0710/TangTang/assets/133496610/53d67aa4-1a3a-4c64-82dd-4ece66c2cabd)


>Skill Info
#### 레벨업을 할 시 선택할 수 있는 스킬 3개를 보여줘야하는데 어떻게 할지 고민하다가 스킬을 배열에 담아 랜덤으로 인덱스 값을 가져오는 방식으로 했습니다.
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
#### 레벨업은 간단하게 경험치바를 2배로 올려주는 방식을 설정했습니다. 이렇게 하는 대신 적의 경험치는 점점 높아져야 할 것을 의미합니다.
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
## PlayerController
- CreateSkillWidget(레벨업시 게임화면에 Skill고르는 위젯 생성)
	- 게임을 멈춤(안 멈추면 적한테 죽을 수 있음) 
	- UIOnly모드로 바꿔줍니다.
 	- bShowMouseCursor = true 마우스 커서를 보여줍니다.
  	- 각 버튼을 바인딩해줍니다. 
- OnSkillButtonClick(해당 스킬 버튼 클릭)
  	- 캐릭터는 그스킬을 가지게 되거나 레벨업

>CreateSkillWidget 소스
```C++
void ATangTangPlayerController::CreateSkillWidget()
{
	if (SkillChooseWidgetClass)
	{
		SkillChooseWidget = CreateWidget<USkillChooseWidget>(this, SkillChooseWidgetClass);
		if (SkillChooseWidget)
		{
			SkillChooseWidget->AddToViewport(); // 위젯 뷰포트

			UGameplayStatics::SetGamePaused(this,true); // 게임을 멈춤
			FInputModeUIOnly InputModeUIOnly; //UIOnly모드로 바꿈
			InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputModeUIOnly.SetWidgetToFocus(SkillChooseWidget->GetCachedWidget());
			SetInputMode(InputModeUIOnly); //InputMode설정
			bShowMouseCursor = true; //마우스커 보이게
			FOnButtonClickedEvent OnButtonClickedEvent;

			/* 바인딩*/
			SkillChooseWidget->Skill1Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::OnSkill1ButtonClick);
			SkillChooseWidget->Skill2Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::OnSkill2ButtonClick);
			SkillChooseWidget->Skill3Button->OnClicked.AddDynamic(
				this, &ATangTangPlayerController::OnSkill3ButtonClick);
		}
	}
}
```
> SkillWidget

![캡처](https://github.com/Junghyeon0710/TangTang/assets/133496610/7f61cc11-eadc-4870-83c3-9239c61f9189)

## Weapon
- Attach weapon(무기를 붙여줌)
- SpawnProjectile(총알을 발사)

>Weapon Blueprint
#### ArrowComponet를 이용하여 블루프린트로 총알 위치를 원하는 위치로 구현할 수 있게 했습니다. 이렇게 하면 코드를 몰라도 위치를 지정할 수 있습니다.
![캡처](https://github.com/Junghyeon0710/TangTang/assets/133496610/8bb4eb84-e2cc-4c0d-b23f-7a0aa13079ea)
#### ArrowComponet를 사용함으로써 방향을 알 수 있습니다.

## Skill
#### 스킬이 가지고 있어야 변수와 함수를 갖고 있는 스킬 부모 클래스
- SKillExecute(스킬 실행)
	- 가상함수로 해서 자식들은 각 스킬의 기능을 구현해야함 
- Overlap(겹칠시 데미지, 많은 적들이 나올 예정이므로 오버랩을 사용)

>데미지
#### 인터페이스를 활용해서 코드 재사용성을 높였습니다.
```C++
void ASkill::SphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// HitInterface를 구현한 액터인지 확인
		IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
		if (HitInterface)
		{
			// 데미지 적용
			HitInterface->GetHit(SkillDamage);

			// 오버랩 사운드 재생
			if (SkillOverlapSound)
			{
				UGameplayStatics::PlaySound2D(this, SkillOverlapSound);
			}

			// 오버랩 파티클 스폰
			if (SkillOverlapParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillOverlapParticle, OtherActor->GetTransform());
			}
		}
	}
}
```
###Skill Child
- Guardian
	- 캐릭터 주위를 공전하며 오버랩시 데미지를 줌
 	- 레벨업당 하나씩 늘어남
- HealthPlus
	- 최대체력을 올려줌
- Lightning
	- 캐릭터 주위에 번개가 떨어집니다.
 	- 캐릭터에 BoxComponet를 붙여 RandomPointInBoundingBox함수를 사용해서 떨어질 위치를 랜덤으로 구했습니다.
  	- 레벨업시 하나씩 늘어납니다.
 - Molotovocockail(화염병)
 	- 먼저 화염병매쉬를 UProjectileMovementComponent사용하여 스폰합니다.
    	- 화염병이 바닥에 히트하면 Destroy후 바닥에 화염파티클을 스폰합니다.
     	- 3초간 오버랩시 지속되며 데미지를 줍니다.
	- 레벨업시 하나씩 늘어납니다.
- ProjectilePlus
  	- 무기가 총발사 할때 하나 추가해서 나갑니다
  	- 레벨업시 하나씩 늘어납니다.
- ProjectileSpeedUp
  	- 스킬 스폰 타이머에 Rate를 빠르게해서 빨리 스폰되게 했습니다.
- Torando
	- 캐릭터 주위에 토네이도를 발사합니다.
 	- 레벨업시 하나씩 늘어납니다.


>Guardian 구현 방식입니다.
```C++
void AGuardian::UpdateGuardianLocation()
{
	// 플레이어 캐릭터 레퍼런스 획득
	TangTangCharacter = TangTangCharacter == nullptr ? Cast<ATangTangCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) : TangTangCharacter;

	if (TangTangCharacter)
	{
		// 가디언의 위치 설정
		SetActorLocation(TangTangCharacter->GetActorLocation());

		// 가디언의 스피어 컴포넌트 위치 설정
		SphereOverlap->SetRelativeLocation(FVector(
			UKismetMathLibrary::DegCos(GuardianTime) * GuardianRadiusX,
			UKismetMathLibrary::DegSin(GuardianTime) * GuardianRadiusY,
			0.f));

		// 가디언 시간 업데이트
		if (GetWorld()->DeltaTimeSeconds * GuardianSpeed + GuardianTime > 360.f)
		{
			GuardianTime = 0;
		}
		else
		{
			GuardianTime = GetWorld()->DeltaTimeSeconds * GuardianSpeed + GuardianTime;
		}
	}
}
```
#### 나머지는 깃허브에서 보실 수 있습니다.

## Item
#### 아이템이 가지고 있어야 변수와 함수를 갖고 있는 스킬 부모 클래스
- 오버랩시 아이템 효과가 사용됩니다.

>Item Child
- Sapwn Exp
	- 적이 죽을시 스폰하는 경험치입니다.
- Health Box
  	- 일정 시간이 지나면 맵 주위에 스폰되는 힐 박스입니다.
  	- 캐릭터 무기의 Projectile이 오버랩시 상자가 열리며 체력회복 아이템이 스폰됩니다.
- Heal
	- Health Box가 Destroy될 시 스폰
   	- 체력회복
  
## Enemy
 - GetHit(데미지 입을 시)
 	- HitInterface에서 상속받음
  	- 적 체력에서 받은 데미지를 빼줌
   	- 0보다 같거나 작으면 죽음   
 - Overlap(오버랩 될 시 캐릭터한테 데미지)
 
> GetHit함수 HitInterface 상속받음
```C++
void AEnemy::GetHit(const float& Damage)
{
	EnemyHealth -= Damage;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorTransform());
	if (EnemyHealth <= 0)
	{
		AEnemy::DieNum++;
		EnemyDie();
	}
}
```
### EnemyBoss
- 따로 C++ 클래스는 없으며 Enemy클래스 블루프린트로 체력하고 몸집만 커지게 구현했습니다.
- 라운드마다 적이 정해진 수 만큼 죽으면 라운드 보스가 나옵니다.
  
## EnemyController
 - MoveToActor(플레이어를 쫓아감)
 - SetFocus(플레이어를 쳐다보게함)
### Tick함수를 사용해서 계속 실행되게했습니다.
>Tick함수
```C++
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn, CharacterRadius, false);
        SetFocus(PlayerPawn);
    }
}
```
## GameMode
- SpawnEnemy(적을 스폰)
	- 라운드 적을 죽인 카운트가 일정 수 넘으면 보스를 스폰합니다.
- 게임 노래 재생
>SpawnEnemy코드
```C++
void ATangTangGameMode::SpawnEnemy(const FTransform& SpawnTransform)
{
	if(AEnemy::DieNum> BossCount)
	{
		CreateWidget(GetWorld(), BossWidget)->AddToViewport(); //보스 경고 위젯 및 애니메이션
		GetWorld()->SpawnActor<AEnemy>(BossEnemy[GameLevel], SpawnTransform); //보스 소환
		AEnemy::DieNum = 0; //카운트0
		++GameLevel; //레벨 증가
	}
	GetWorld()->SpawnActor<AEnemy>(Enemy[GameLevel], SpawnTransform);
}
```
## UI
- CharacterOverlay(캐릭터 기본화면 UI)
	- EXP, 게임시간, 체력등을 보여줌
 - SkillChoseWidget
   	- 캐릭터가 레벨업 할 시 생성되는 UI
- DieWidget
  	- 캐릭터가 죽을시 생성
- BossWarningWidget
	- 보스 경고 위젯
 	- 보스가 나올시 생성  
