// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Lobby_PC.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API ALobby_PC : public APlayerController
{
	GENERATED_BODY()
	


#pragma region Public Function
public:
	virtual void BeginPlay() override;
#pragma endregion
};
