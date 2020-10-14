// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnProjectile.h"


// Sets default values
AMonsterSpawnProjectile::AMonsterSpawnProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMonsterSpawnProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterSpawnProjectile::StartFunction_Implementation(const FHitResult& Hit)
{
	if (!HasAuthority())
	{
		return;
	}

	//Spawn Monster 
	if (ProjectileInfo.SpawnActorClass)
	{
		FTransform transform;
		transform.SetLocation(Hit.Location);
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		params.Owner = GetOwner();
		AActor* monster = GetWorld()->SpawnActor<AActor>(ProjectileInfo.SpawnActorClass, transform, params);

		if (!monster)		//Check Monster Spawn Success.
		{
			//Don't CoolDown Start
			UE_LOG(LogClass, Warning, TEXT("Failed to Spawn Monster"));
		}
	}

}

