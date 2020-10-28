// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon0.generated.h"

UCLASS()
class TEAMPORTFOLIO_API AWeapon0 : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* WeaponMesh;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float WeaponDamage = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float WeaponAttackSpeed = 0.05f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	int MaxBullet = 30;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	int CurrentBullet = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	int RemainedBullet=60;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status", Meta=(ClampMin = 0.0f, ClampMax = 1.5f))
	float WeaponRecoil = 0.1f;

	UFUNCTION()
	void OnFire();

	void OnFireShotgun();

	void OnFireGranade();

	float InterpPitch =0.0f;

	void StartRecoil();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	int ShotgunBullet = 15;


	//TArray<int> WeaponBullet;



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


	FTimerHandle FireTimerHandle;

	FTimerHandle FireTimerHandle2;

	FTimerHandle Weapon1_FireTimerHande;
	FTimerHandle Weapon1_FireTimerHande2;



public:	
	// Sets default values for this actor's properties
	AWeapon0();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
