// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TeamP_BasicPlayer.generated.h"

DECLARE_DELEGATE_OneParam(FBindActionParamDelegate, int32);

UCLASS()
class TEAMPORTFOLIO_API ATeamP_BasicPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATeamP_BasicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UCameraComponent* Camera;


	// 무기 여기있음
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UWeaponComponent* Weapon1;




	//앞뒤양옆 이동, 상하좌우 카메라 이동
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);

	void Sprint();
	void StopSprint();

	void WeaponChange1();
	void WeaponChange2();
	void WeaponChange3();
	void WeaponChange4();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float WalkSpeed = 300.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float SprintSpeed = 600.0f;


	//앉기, 언리얼에서 어느정도 지원해줌
	void StartCrouch();

	void StartIronsight();
	void StopIronsight();

	FRotator GetAimOffset() const;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float CurrentHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MaxHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackDamage;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnFire();

	UFUNCTION()
	void OnSpawnFire();

	FTimerHandle *FireTimerHandle;

	FTimerHandle *FireTimerHandle2;

	FTimerHandle Weapon1_FireTimerHande;
	FTimerHandle Weapon1_FireTimerHande2;
	


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		class UParticleSystem* HitEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		class UParticleSystem* BloodHitEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		class UParticleSystem* MuzzleFlash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		class USoundBase* WeaponSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UMaterialInstance* NormalDecal;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsIronsight : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status") //샷건임???
	uint64 bIsShotgun : 1;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsReload : 1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsFire : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsFireAnim : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bFireShotgun : 1;


	void StartFire();

	void StopFire();

	void Reload();

	//발사가능체크
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bCanFire : 1;

	void CheckCanFire();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Data")
	class UAnimMontage* ReloadMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Data")
	class UAnimMontage* DeadMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Data")
	class UAnimMontage* HitMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Data")
	class UAnimMontage* ChangeWeaponMontage;


	//무기 변경 
	void WeaponChange(int WeaponNumber);



	UPROPERTY(BlueprintReadOnly)
		float WeaponDamageC = 1.0f;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float WeaponAttackSpeed = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASpawnTest> ProjectileClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class AWeapon0* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<class AWeapon0>> WeaponClasses;


	int UsingWeaponNumber;

	void LoadWeapon(int Index);


};
