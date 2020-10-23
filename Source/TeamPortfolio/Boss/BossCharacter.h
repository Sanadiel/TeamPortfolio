// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStaticsTypes.h"/*FPredictProjectilePathParams & FPredictProjectilePathResult*/
#include "BossCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class ABossProjectileBase;
class USkeletalMeshComponent;
class UHandMeshComponent;
class UBossWidgetBase;
class UPhysicsHandleComponent;
class USceneComponent;
class UMotionControllerComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UMotionControllerComponent* VR_Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UMotionControllerComponent* VR_Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UHandMeshComponent* VR_LeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UHandMeshComponent* VR_RightHand;


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
		TArray<TSubclassOf<ABossProjectileBase>> ProjectileClasses;

	//Current Cooldown.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
		TArray<float> SpawnCooldown;

	//MaxCoolDown.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
		TArray<float> MaxSpawnCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UMG")
		TSubclassOf<UBossWidgetBase> BossWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Grab")
		bool bIsGrabbed;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Hold Projectile Actor. Call From "SearchHold"
	UFUNCTION(Server, Reliable)
		void HoldSpawnProjectile(ABossProjectileBase* ProjectileObject);
		void HoldSpawnProjectile_Implementation(ABossProjectileBase* ProjectileObject);

	//Release when it is holding something, if not hold anything, find actor to hold.
	void HandAction();

	void LeftHandAction();
	void RightHandAction();


	void CreateUI();

	//Search that Want to Hold, And Hold that.
	UFUNCTION(Server, Reliable)
		void SearchHold(FVector TraceStart, FVector TraceEnd);
	void SearchHold_Implementation(FVector TraceStart, FVector TraceEnd);

	//Release Will do at Server Only.
	UFUNCTION(Server, Reliable)
		void ReleaseHold();
	void ReleaseHold_Implementation();

	//UI Using.
	UFUNCTION(Server, Reliable)
		void SpawnProjectile(int32 Index);
	void SpawnProjectile_Implementation(int32 Index);

	UFUNCTION(NetMulticast, Reliable)
		void ResetCooldown(int32 Index);
	void ResetCooldown_Implementation(int32 Index);

};
