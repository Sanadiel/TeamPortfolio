// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossObject.h"
#include "MonsterSpawnProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USkeletalMeshComponent;

UCLASS()
class TEAMPORTFOLIO_API AMonsterSpawnProjectile : public AActor
{
	GENERATED_BODY()

public:

	/*Warning. This Actor Had Projectile Movement Component in the Past. But, after the change to Throwing PlayMode, Projectile Component is Deleted. So, Do Not Use This As Having Projectile Movement Component.*/

	// Sets default values for this actor's properties
	AMonsterSpawnProjectile();

	//Sphere Collision
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
		USphereComponent* Sphere;

	//// Projectile movement component. Not Used when holding.
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	//	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		USkeletalMeshComponent* Mesh;

	////Monster Class To Spawn.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Monster")
	//	TSubclassOf<AActor> MonsterActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		FMonsterSpawnInfo MonsterSpawnInfo;

	//true Means "Spawn OK"
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
		bool bActivated;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(Server, Reliable)
	void SpawnMonster(const FHitResult& Hit);
	void SpawnMonster_Implementation(const FHitResult& Hit);
};