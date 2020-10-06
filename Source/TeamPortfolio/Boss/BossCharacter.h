// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStaticsTypes.h"/*FPredictProjectilePathParams & FPredictProjectilePathResult*/
#include "BossCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AMonsterSpawnProjectile;
class UBossWidgetBase;
class UPhysicsHandleComponent;
class USceneComponent;

UCLASS()
class TEAMPORTFOLIO_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossCharacter();

	//Camera Boon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* HoldPosition;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	//Draw Trajectory in Tick. Deprecated.
	FPredictProjectilePathParams TrajectoryParams;
	FPredictProjectilePathResult Trajectoryresult;
	void DrawProjectileTrajectory();
	*/

	/*Movement Functions*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	////Fire & Spawn Monsters
	//void FireToSpawn();

	//List that You Can.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Monster")
	TArray<TSubclassOf<AMonsterSpawnProjectile>> SpawnClasses;

	//Current Cooldown.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
	TArray<float> SpawnCooldown;

	//MaxCoolDown.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
		TArray<float> MaxSpawnCooldown;


	//Currently Selected Projectile Class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Monster")
	TSubclassOf<AMonsterSpawnProjectile> MonsterSpawnProjectileClass;

	//Change Projectile Class --> Will Use In Boss UI Button.
	void SetProjectileClass(TSubclassOf<AMonsterSpawnProjectile> NewProjectileClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UMG")
		TSubclassOf<UBossWidgetBase> BossWidgetClass;

	//Hold Projectile Actor.
	UFUNCTION(Server,Reliable)
	void HoldSpawnProjectile(AMonsterSpawnProjectile* ProjectileObject);
	void HoldSpawnProjectile_Implementation(AMonsterSpawnProjectile* ProjectileObject);

	//Release when it is holding something, if not hold anything, find actor to hold.
	void HandAction();

	//Return Current GrabbedComponent.
	UPrimitiveComponent* GetGrabbedComponent() const;
};
