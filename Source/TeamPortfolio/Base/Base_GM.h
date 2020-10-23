// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Base_GM.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API ABase_GM : public AGameModeBase
{
	GENERATED_BODY()
	

#pragma region Public Function
public:
	AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT(""));

	UFUNCTION(NetMulticast, Reliable)
	void Replace_AllPlayers(); 
	void Replace_AllPlayers_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Replace_Player(AController* Player);
	void Replace_Player_Implementation(AController* Player);

#pragma endregion
};
