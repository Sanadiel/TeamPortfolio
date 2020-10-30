// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MasterLobby_GS.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API AMasterLobby_GS : public AGameStateBase
{
	GENERATED_BODY()
	
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Network")
	TArray<bool> ReadyButton;

#pragma endregion

#pragma region Public Function
	AMasterLobby_GS();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma endregion
};
