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
