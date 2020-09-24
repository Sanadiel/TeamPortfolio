// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BossObject.Generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FMonsterSpawnInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<AActor> SpawnActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture2D* Thumbnail;
};