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
#pragma region Public Member
public:
	TArray<AActor*> Buttons;

#pragma endregion

#pragma region Public Function
public:
	UFUNCTION()
	void StartGame();

	virtual void BeginPlay() override;

	virtual void Setting();

	//CheckButton
	FTimerHandle ButtonTimer;

	UFUNCTION(BlueprintCallable)
	virtual void StartCheckButton();

	UFUNCTION()
	virtual void CheckButton();


	//Time
	FTimerHandle LobbyTimer;

	UFUNCTION(BlueprintCallable)
	void StartCountDown();

	UFUNCTION()
	void DecreaseTime();

#pragma endregion
	
};
