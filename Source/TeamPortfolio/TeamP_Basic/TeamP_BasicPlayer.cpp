// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamP_BasicPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameframeWork/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "WeaponComponent.h"
#include "TeamP_BasicPC.h"
#include "BulletDamageType.h"
#include "Components/DecalComponent.h"
#include "SpawnTest.h"
#include "../MainUI/MainUIBase.h"
#include "../Item/Inventory.h"
#include "../Item/MasterItem.h"
#include "Weapon0.h"


// Sets default values
ATeamP_BasicPlayer::ATeamP_BasicPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	//카메라
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->SocketOffset = FVector(0, 40.0f, 88.f);
	SpringArm->TargetArmLength = 120.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//무기 추가
	Weapon1 = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon1"));
	Weapon1->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));


	Tags.Add(TEXT("Player"));


}

// Called when the game starts or when spawned
void ATeamP_BasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	WeaponChange(0);
	Weapon1->SetHiddenInGame(true);
	//CurrentWeapon->CurrentBullet = CurrentWeapon->MaxBullet;

}

// Called every frame
void ATeamP_BasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ATeamP_BasicPC* PC = GetController<ATeamP_BasicPC>();
	//if (IsValid(PC))
	//{
	//	PC->GetMainUI()->UpdateHpBar(CurrentHP / MaxHP);
	//}
}

// 플레이어 입력
void ATeamP_BasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATeamP_BasicPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATeamP_BasicPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATeamP_BasicPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATeamP_BasicPlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATeamP_BasicPlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ATeamP_BasicPlayer::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ATeamP_BasicPlayer::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ATeamP_BasicPlayer::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ATeamP_BasicPlayer::StartCrouch);

	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &ATeamP_BasicPlayer::StartIronsight);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Released, this, &ATeamP_BasicPlayer::StopIronsight);

	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ATeamP_BasicPlayer::Reload);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATeamP_BasicPlayer::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ATeamP_BasicPlayer::StopFire);


	//무기변경입력, 인벤토리 추가해서 인벤토리에서 무기바꿀시 삭제 or 변경

	PlayerInputComponent->BindAction<FBindActionParamDelegate>(TEXT("Weaponchange1"), IE_Pressed, this, &ATeamP_BasicPlayer::WeaponChange,0);
	PlayerInputComponent->BindAction<FBindActionParamDelegate>(TEXT("Weaponchange2"), IE_Pressed, this, &ATeamP_BasicPlayer::WeaponChange,1);
	PlayerInputComponent->BindAction<FBindActionParamDelegate>(TEXT("Weaponchange3"), IE_Pressed, this, &ATeamP_BasicPlayer::WeaponChange,2);
	PlayerInputComponent->BindAction<FBindActionParamDelegate>(TEXT("Weaponchange4"), IE_Pressed, this, &ATeamP_BasicPlayer::WeaponChange,3);


}

//앞뒤좌우이동, 상하좌우카메라
void ATeamP_BasicPlayer::MoveForward(float AxisValue)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FRotator YawBaseRotation = FRotator(0, GetControlRotation().Yaw, 0);

	FVector CameraForward = UKismetMathLibrary::GetForwardVector(YawBaseRotation);

	AddMovementInput(CameraForward, AxisValue);

}

void ATeamP_BasicPlayer::MoveRight(float AxisValue)
{

	FVector CameraLocation;
	FRotator CameraRotation;

	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FRotator YawBaseRotation = FRotator(0, GetControlRotation().Yaw, 0);

	FVector CameraRight = UKismetMathLibrary::GetRightVector(YawBaseRotation);

	AddMovementInput(CameraRight, AxisValue);

}

void ATeamP_BasicPlayer::LookUp(float AxisValue)
{

	AddControllerPitchInput(AxisValue);

}

void ATeamP_BasicPlayer::Turn(float AxisValue)
{

	AddControllerYawInput(AxisValue);

}

void ATeamP_BasicPlayer::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ATeamP_BasicPlayer::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}


//앉기
void ATeamP_BasicPlayer::StartCrouch()
{
	if (CanCrouch())
	{
		Crouch();
		UE_LOG(LogClass, Warning, TEXT("coruch"));
	}
	else
	{
		UnCrouch();
		UE_LOG(LogClass, Warning, TEXT("uncoruch"));
	}
}

void ATeamP_BasicPlayer::StartIronsight()
{
	bIsIronsight = true;
}

void ATeamP_BasicPlayer::StopIronsight()
{
	bIsIronsight = false;
}

FRotator ATeamP_BasicPlayer::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}


//데미지 처리

float ATeamP_BasicPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHP <= 0)
	{
		return 0.0f;
	}

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);

		if (PointDamageEvent->HitInfo.BoneName.Compare(TEXT("head")) == 0)
		{
			CurrentHP = 0;
		}
		else
		{
			CurrentHP -= DamageAmount;
		}

		if (HitMontage)
		{
			FString SectionName = FString::Printf(TEXT("Hit%d"), FMath::RandRange(1, 4));
			PlayAnimMontage(HitMontage, 1.0f, FName(SectionName));
		}

		if (CurrentHP <= 0)
		{
			//사망애니메이션
			if (DeadMontage)
			{
				FString SectionName = FString::Printf(TEXT("Death_%d"), FMath::RandRange(1, 3));
				PlayAnimMontage(DeadMontage, 1.0f, FName(SectionName));
			}

			DisableInput(Cast<APlayerController>(GetController()));
		}


	}
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID)) //RadialDamage 처리
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);

		UE_LOG(LogClass, Warning, TEXT("Radial Damage %f"), DamageAmount);
	}
	else //모든 데미지 처리
	{
		CurrentHP -= DamageAmount;
	}


	ATeamP_BasicPC* PC = GetController<ATeamP_BasicPC>();
	if (IsValid(PC))
	{
		PC->GetMainUI()->UpdateHpBar(CurrentHP / MaxHP);
	}

	return 0.0f;
}


//총 발사 후 동작
void ATeamP_BasicPlayer::OnFire()
{


	if (!bIsFire)
	{
		return;
	}

	if (CurrentWeapon->CurrentBullet <= 0 )
	{
		bIsFireAnim = false;
		return;
	}

	if (bIsShotgun) {
		bFireShotgun = true;
	}

	if (bCanFire) //bCanFire로 변경
	{
		
		bIsFireAnim = false;

		CurrentWeapon->CurrentBullet -= 1;

		UE_LOG(LogClass,Warning,TEXT("Bullet = %d / %d"),CurrentWeapon->CurrentBullet,CurrentWeapon->MaxBullet)
		ATeamP_BasicPC* PC = Cast<ATeamP_BasicPC>(GetController());

		if (PC)
		{

			int32 ScreenSizeX;
			int32 ScreenSizeY;

			FVector CrosshairWorldPosition;
			FVector CrosshairWorldDirection;

			FVector CameraLocation;
			FRotator CameraRotation;


			int RandX = FMath::RandRange(1, 2);
			int RandY = FMath::RandRange(1, 2);

			PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
			PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2 + RandX, ScreenSizeY / 2 + RandY, CrosshairWorldPosition, CrosshairWorldDirection);

			PC->GetPlayerViewPoint(CameraLocation, CameraRotation);
			FRotator PlayerRotation = GetControlRotation();
			PlayerRotation.Pitch += FMath::FRandRange(0.2f, 1.0f);
			GetController()->SetControlRotation(PlayerRotation);

			FVector TraceStart = CameraLocation;
			FVector TraceEnd = TraceStart + (CrosshairWorldDirection * 99999.f);

			//C2S_ProcessFire(TraceStart, TraceEnd);

			TArray<TEnumAsByte<EObjectTypeQuery>> Objects;

			Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
			Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
			Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

			TArray<AActor*> ActorToIgnore;

			FHitResult OutHit;

			bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
				GetWorld(),
				TraceStart,
				TraceEnd,
				Objects,
				true,
				ActorToIgnore,
				EDrawDebugTrace::None,
				OutHit,
				true,
				FLinearColor::Red,
				FLinearColor::Green,
				5.0f
			);

			if (Result)
			{
			
					//all client spawn Hiteffect and Decal

					//S2A_SpawnHitEffectAndDecal(OutHit);
					if (Cast<ACharacter>(OutHit.GetActor()))
					{
						//캐릭터
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
							BloodHitEffect,
							OutHit.ImpactPoint + (OutHit.ImpactNormal * 10)
						);
					}
					else
					{
						//지형
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
							HitEffect,
							OutHit.ImpactPoint + (OutHit.ImpactNormal * 10)
						);

						UDecalComponent* NewDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
							NormalDecal,
							FVector(5, 5, 5),
							OutHit.ImpactPoint,
							OutHit.ImpactNormal.Rotation(),
							10.0f
						);

						NewDecal->SetFadeScreenSize(0.005f);

					}

					//Point Damage
					UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), //맞은놈
						WeaponDamageC,	//데미지
						-OutHit.ImpactNormal,	//데미지 방향
						OutHit,	//데미지 충돌 정보
						GetController(),	//때린 플레이어
						this,	//때린놈
						UBulletDamageType::StaticClass() //데미지 타입
					);

					MakeNoise(1.0f, this, OutHit.ImpactPoint); //AI가 센서로 받을 수 있는 Noise를 생성한다.

				
			}

			//All Client Spawn Muzzleflash and Sound
			//S2A_SpawnMuzzleFlashAndSound();


			if (WeaponSound)
			{
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
					WeaponSound,
					CurrentWeapon->WeaponMesh->GetComponentLocation()
				);
			}

			if (MuzzleFlash)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
					MuzzleFlash,
					CurrentWeapon->WeaponMesh->GetSocketTransform(TEXT("Muzzle"))
				);
			}
		}


		//총발사속도 제어용 타이머
		GetWorldTimerManager().SetTimer(*FireTimerHandle,
			this,
			&ATeamP_BasicPlayer::OnFire,
			WeaponAttackSpeed,
			false);

		//반동 애니메이션
		bIsFireAnim = true;

	}
	else {//총발사이후 쿨타임동안 onfire다시 호출하는 타이머, 연사안되는 총을 onfire 연속호출(클릭연타)로 연사되도록하는거 방지함


		GetWorldTimerManager().SetTimer(*FireTimerHandle2,
			this,
			&ATeamP_BasicPlayer::OnFire,
			WeaponAttackSpeed / 4,
			false);
	}
}

void ATeamP_BasicPlayer::OnSpawnFire()
{
}

void ATeamP_BasicPlayer::StartFire() //발사키 입력시 
{

	CheckCanFire();
	if (!bCanFire)
	{
		return;
	}

	bIsFire = true;

	OnFire();

} 

void ATeamP_BasicPlayer::StopFire()
{
	bIsFire = false;
	if (!bIsShotgun) {
		bIsFireAnim = false;
	}
}

void ATeamP_BasicPlayer::Reload()
{
	if (CurrentWeapon->RemainedBullet == 0) {
		return;
	}
	bIsReload = true;

	if(!CurrentWeapon->RemainedBullet == 0){
		if ((CurrentWeapon->RemainedBullet + CurrentWeapon->CurrentBullet) >= CurrentWeapon->MaxBullet) {//남은총알+현재총알이 탄창보다 많을경우 

			CurrentWeapon->RemainedBullet -= (CurrentWeapon->MaxBullet - CurrentWeapon->CurrentBullet);// 남은총알 = 남은총알-(최대총알-현재총알(충전된총알))

			CurrentWeapon->CurrentBullet = CurrentWeapon->MaxBullet;//현재총알 = 최대총알

		}else{																					//남은총알이 30개 이하일  경우
		
			CurrentWeapon->CurrentBullet += CurrentWeapon->RemainedBullet;

			CurrentWeapon->RemainedBullet = 0;
			
		}
	}
	UE_LOG(LogClass, Warning, TEXT("CurrentBullet = %d,MaxBullet = %d, RemainedBullet = %d"), CurrentWeapon->CurrentBullet, CurrentWeapon->MaxBullet, CurrentWeapon->RemainedBullet);
}

//발사가능체크.
void ATeamP_BasicPlayer::CheckCanFire()
{
	// 리로드중인것도 체크해줘야댐
	
	if ((GetWorldTimerManager().IsTimerActive(*FireTimerHandle)) || bIsReload || CurrentWeapon->CurrentBullet <= 0) {
		
		bCanFire = false;
		
	}
	else {
		bCanFire = true;
	}
}




//선택한 무기 표시

void ATeamP_BasicPlayer::WeaponChange(int WeaponNumber)
{
	
	bIsFire = false;
	bIsFireAnim = false;

	FActorSpawnParameters params;
	params.Owner = GetOwner();
	//transform.SetLocation(GetActorLocation());

		AWeapon0* SpawnWeapon = GetWorld()->SpawnActor<AWeapon0>(WeaponClasses[WeaponNumber], params);

		if (SpawnWeapon)
		{
			UE_LOG(LogClass, Warning, TEXT("SpawnWeapon %d"), WeaponNumber);
			SpawnWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));//소켓은 스켈레탈메시에 있음.따라서 parent는 GetMesh()해준것.
			if (CurrentWeapon)
			{
				CurrentWeapon->Destroy();
			}
			CurrentWeapon = SpawnWeapon;
		}
		WeaponAttackSpeed = CurrentWeapon->WeaponAttackSpeed;
		WeaponDamageC = CurrentWeapon->WeaponDamage;
		bIsShotgun = false;
	
		UE_LOG(LogClass, Warning, TEXT("WeaponNumber : %d  MaxBullet : %d  Bullet : %d / %d"), WeaponNumber, CurrentWeapon->MaxBullet, CurrentWeapon->CurrentBullet, CurrentWeapon->RemainedBullet);


	//GetWorld()->GetTimeSeconds();

	////header
	//TArray<float> Cooldown;

	//Cooldown->Add(0.0f);

	//tick()
	//	for ()
	//		Cooldown[i] += deltasecond;

	FireTimerHandle = &Weapon1_FireTimerHande;
	FireTimerHandle2 = &Weapon1_FireTimerHande2;

	/*switch (WeaponNumber)
	{
	case 1: WeaponNumber = 1;
		Weapon1->SetHiddenInGame(false);
		Weapon2->SetHiddenInGame(true);
		Weapon3->SetHiddenInGame(true);
		Weapon4->SetHiddenInGame(true);
		break;
	case 2: WeaponNumber = 2;
		Weapon1->SetHiddenInGame(true);
		Weapon2->SetHiddenInGame(false);
		Weapon3->SetHiddenInGame(true);
		Weapon4->SetHiddenInGame(true);
		break;
	case 3: WeaponNumber = 3;
		Weapon1->SetHiddenInGame(true);
		Weapon2->SetHiddenInGame(true);
		Weapon3->SetHiddenInGame(false);
		Weapon4->SetHiddenInGame(true);
		break;
	case 4: WeaponNumber = 4;
		Weapon1->SetHiddenInGame(true);
		Weapon2->SetHiddenInGame(true);
		Weapon3->SetHiddenInGame(true);
		Weapon4->SetHiddenInGame(false);
		break;
	}*/
}


//무기 옵션들 




void ATeamP_BasicPlayer::LoadWeapon(int Index)
{
	//ATeamP_BasicPC* PC = GetController<ATeamP_BasicPC>();
	//if (IsValid(PC))
	//{
	//	switch (Index)
	//	{
	//	case 1:

	//		break;
	//	case 2:

	//		break;
	//	case 3:

	//		break;
	//	case 4:

	//		break;
	//	default:
	//		break;
	//	}	
	//	
	//	//PC->Inventory->Equipment[Index]->ItemData.;
	//	
	//	//PC->Inventory->Equipment[Index]->StaticMesh;//StaticMesh
	//}
}
