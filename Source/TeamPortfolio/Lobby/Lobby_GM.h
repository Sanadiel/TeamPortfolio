// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lobby_GM.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API ALobby_GM : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Public Function
public:
	FTimerHandle LobbyTimer;

	UFUNCTION()
	void StartGame();

	virtual void BeginPlay() override;

	UFUNCTION()
	void DecreaseTime();

#pragma endregion
	
};
