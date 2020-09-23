// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Normal			=	0	UMETA(Display = "Normal"),
	Battle			=	0	UMETA(Display = "Battle"),
	Chase			=	0	UMETA(Display = "Chase"),
	Death			=	0	UMETA(Display = "Death"),
};

UCLASS()
class TEAMPORTFOLIO_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	EMonsterState CurrentState;

};
