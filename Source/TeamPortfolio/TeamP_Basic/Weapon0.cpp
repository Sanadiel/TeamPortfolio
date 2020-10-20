// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon0.h"

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

