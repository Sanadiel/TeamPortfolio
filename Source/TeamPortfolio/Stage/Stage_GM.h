// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage_GM.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API AStage_GM : public AGameModeBase
{
	GENERATED_BODY()
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Boss")
	TSubclassOf<class ABossCharacter> Boss;

#pragma endregion
	

#pragma region Public Function
public:
	AStage_GM();
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;

	
#pragma endregion
};
