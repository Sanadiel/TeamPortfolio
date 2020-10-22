// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon0.h"
#include "TeamP_BasicPlayer.h"
#include "TeamP_BasicPC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "BulletDamageType.h"
#include "../MainUI/MainUIBase.h"
#include "../MainUI/WeaponInfoBase.h"

void AWeapon0::OnFire()
{
	ATeamP_BasicPlayer* Player = Cast<ATeamP_BasicPlayer>(GetOwner());//�����վ�?

	UE_LOG(LogClass, Warning, TEXT("OnFire"))

		
	if (Player) {



		if (!(Player->bIsFire)|| Player->bIsReload || Player->bIsWeaponChange)
		{
			UE_LOG(LogClass, Warning, TEXT("return onfire"))
				Player->bIsFire = false;
			Player->bIsFireAnim = false;
			return;
		}

	

		if (Player->CurrentWeapon->CurrentBullet <= 0)
		{
			Player->bIsFireAnim = false;
			return;
		}

		if (Player->bIsShotgun) {
			Player->bFireShotgun = true;
		}

		if (Player->bCanFire) //bCanFire�� ����
		{

			Player->bIsFireAnim = false;

			Player->CurrentWeapon->CurrentBullet -= 1;

			UE_LOG(LogClass, Warning, TEXT("Bullet = %d / %d"), Player->CurrentWeapon->CurrentBullet, Player->CurrentWeapon->MaxBullet);

			ATeamP_BasicPC* PC = Cast<ATeamP_BasicPC>(Player->GetController());

			PC->GetMainUI()->WeaponInfo->SetIBulletNum(Player->CurrentWeapon->CurrentBullet);

			if (PC)
			{

				int32 ScreenSizeX;
				int32 ScreenSizeY;

				FVector CrosshairWorldPosition;
				FVector CrosshairWorldDirection;

				FVector CameraLocation;
				FRotator CameraRotation;

				PC->GetViewportSize(ScreenSizeX, ScreenSizeY);

				int RandX = FMath::RandRange(1, 2);
				int RandY = FMath::RandRange(1, 2);

				PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2 + RandX, ScreenSizeY / 2 + RandY, CrosshairWorldPosition, CrosshairWorldDirection);

				PC->GetPlayerViewPoint(CameraLocation, CameraRotation);
				FRotator PlayerRotation = Player->GetControlRotation();
				PlayerRotation.Pitch += FMath::FRandRange(0.2f, 0.5f);
				Player->GetController()->SetControlRotation(PlayerRotation);

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
						//ĳ����
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
							BloodHitEffect,
							OutHit.ImpactPoint + (OutHit.ImpactNormal * 10)
						);
					}
					else
					{
						//����
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
					UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), //������
						WeaponDamage,	//������
						-OutHit.ImpactNormal,	//������ ����
						OutHit,	//������ �浹 ����
						Player->GetController(),	//���� �÷��̾�
						this,	//������
						UBulletDamageType::StaticClass() //������ Ÿ��
					);

					MakeNoise(1.0f, Player, OutHit.ImpactPoint); //AI�� ������ ���� �� �ִ� Noise�� �����Ѵ�.


				}

				//All Client Spawn Muzzleflash and Sound
				//S2A_SpawnMuzzleFlashAndSound();


				if (WeaponSound)
				{
					UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
						WeaponSound,
						WeaponMesh->GetComponentLocation()
					);
				}

				if (MuzzleFlash)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
						MuzzleFlash,
						WeaponMesh->GetSocketTransform(TEXT("Muzzle"))
					);
				}
			}


			//�ѹ߻�ӵ� ����� Ÿ�̸�
			GetWorldTimerManager().SetTimer(FireTimerHandle,
				this,
				&AWeapon0::OnFire,
				WeaponAttackSpeed,
				false);


			//�ݵ� �ִϸ��̼�
			Player->bIsFireAnim = true;
		}
		else {//�ѹ߻����� ��Ÿ�ӵ��� onfire�ٽ� ȣ���ϴ� Ÿ�̸�, ����ȵǴ� ���� onfire ����ȣ��(Ŭ����Ÿ)�� ����ǵ����ϴ°� ������


			GetWorldTimerManager().SetTimer(FireTimerHandle2,
				this,
				&AWeapon0::OnFire,
				WeaponAttackSpeed / 4,
				false);
		}
	}
}

void AWeapon0::OnFireShotgun()												//����
{
	ATeamP_BasicPlayer* Player = Cast<ATeamP_BasicPlayer>(GetOwner());

	UE_LOG(LogClass, Warning, TEXT("OnFireShotgun"))

		if (Player) {

				if (!(Player->bIsFire))
				{
					return;
				}


				if (Player->CurrentWeapon->CurrentBullet <= 0)
				{
					Player->bIsFireAnim = false;
					return;
				}

			if (Player->bIsShotgun) {
				Player->bFireShotgun = true;
			}

			if (Player->bCanFire) //bCanFire�� ����
			{

				Player->bIsFireAnim = false;

				Player->CurrentWeapon->CurrentBullet -= 1; 

				UE_LOG(LogClass, Warning, TEXT("Bullet = %d / %d"), Player->CurrentWeapon->CurrentBullet, Player->CurrentWeapon->MaxBullet);

				ATeamP_BasicPC* PC = Cast<ATeamP_BasicPC>(Player->GetController());

				PC->GetMainUI()->WeaponInfo->SetIBulletNum(Player->CurrentWeapon->CurrentBullet);


				if (PC)
				{

					int32 ScreenSizeX;
					int32 ScreenSizeY;

					FVector CrosshairWorldPosition;
					FVector CrosshairWorldDirection;

					FVector CameraLocation;
					FRotator CameraRotation;

					FHitResult OutHit;

					for (int i = 0; i <= ShotgunBullet;i++) {

						int RandX = FMath::RandRange(1, 30);
						int RandY = FMath::RandRange(1, 30);

						PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
						PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2 + RandX, ScreenSizeY / 2 + RandY, CrosshairWorldPosition, CrosshairWorldDirection);

						PC->GetPlayerViewPoint(CameraLocation, CameraRotation);
						FRotator PlayerRotation = Player->GetControlRotation();
						PlayerRotation.Pitch += FMath::FRandRange(0.2f, 0.5f);
						Player->GetController()->SetControlRotation(PlayerRotation);

						FVector TraceStart = CameraLocation;
						FVector TraceEnd = TraceStart + (CrosshairWorldDirection * 99999.f);

						//C2S_ProcessFire(TraceStart, TraceEnd);

						TArray<TEnumAsByte<EObjectTypeQuery>> Objects;

						Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
						Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
						Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

						TArray<AActor*> ActorToIgnore;

						//FHitResult OutHit;



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
								//ĳ����
								UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
									BloodHitEffect,
									OutHit.ImpactPoint + (OutHit.ImpactNormal * 10)
								);
							}
							else
							{
								//����
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
							UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), //������
								WeaponDamage,	//������
								-OutHit.ImpactNormal,	//������ ����
								OutHit,	//������ �浹 ����
								Player->GetController(),	//���� �÷��̾�
								this,	//������
								UBulletDamageType::StaticClass() //������ Ÿ��
							);

							


						}
					}
					//All Client Spawn Muzzleflash and Sound
					//S2A_SpawnMuzzleFlashAndSound();
					MakeNoise(1.0f, Player, OutHit.ImpactPoint); //AI�� ������ ���� �� �ִ� Noise�� �����Ѵ�.

					if (WeaponSound)
					{
						UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
							WeaponSound,
							WeaponMesh->GetComponentLocation()
						);
					}

					if (MuzzleFlash)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
							MuzzleFlash,
							WeaponMesh->GetSocketTransform(TEXT("Muzzle"))
						);
					}
				}


				//�ѹ߻�ӵ� ����� Ÿ�̸�
				GetWorldTimerManager().SetTimer(FireTimerHandle,
					this,
					&AWeapon0::OnFireShotgun,
					WeaponAttackSpeed,
					false);


				//�ݵ� �ִϸ��̼�
				Player->bIsFireAnim = true;
				Player->bFireShotgun = true;
			}
			else {//�ѹ߻����� ��Ÿ�ӵ��� onfire�ٽ� ȣ���ϴ� Ÿ�̸�, ����ȵǴ� ���� onfire ����ȣ��(Ŭ����Ÿ)�� ����ǵ����ϴ°� ������


				GetWorldTimerManager().SetTimer(FireTimerHandle2,
					this,
					&AWeapon0::OnFireShotgun,
					WeaponAttackSpeed / 4,
					false);
			}
		}

}




// Sets default values
AWeapon0::AWeapon0()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

}


// Called when the game starts or when spawned
void AWeapon0::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon0::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

