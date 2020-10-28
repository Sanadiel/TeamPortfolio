// Fill out your copyright notice in the Description page of Project Settings.


#include "Granade.h"

// Sets default values
AGranade::AGranade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGranade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGranade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

