// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestUI_GS.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API ATestUI_GS : public AGameStateBase
{
	GENERATED_BODY()
	
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FString> MonsterNameArray;

#pragma endregion

#pragma region Public Function
public:
	ATestUI_GS();

	virtual void BeginPlay() override;
	FString GetName(int Value);

#pragma endregion
};
