// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStaticsTypes.h"/*FPredictProjectilePathParams & FPredictProjectilePathResult*/
#include "BossCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AMonsterSpawnProjectile;
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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Draw Trajectory in Tick.*/
	FPredictProjectilePathParams TrajectoryParams;
	FPredictProjectilePathResult Trajectoryresult;
	void DrawProjectileTrajectory();

	/*Movement Functions*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	//Fire & Spawn Monsters
	void FireToSpawn();

	//What Monster You Want to Spawn?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Monster")
		TSubclassOf<AMonsterSpawnProjectile> MonsterSpawnProjectileClass;

	//Change Projectile Class --> Will Use In Boss UI Button.
	void SetProjectileClass(TSubclassOf<AMonsterSpawnProjectile> NewProjectileClass);

};
