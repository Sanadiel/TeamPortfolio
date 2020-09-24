// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TotalLog_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UTotalLog_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Kill_Log")
	TArray<int> KillLog;
	
};
