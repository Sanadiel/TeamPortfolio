// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterDataTable.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct TEAMPORTFOLIO_API FMonsterDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MonsterID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MonsterName;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TAssetPtr<class UTexture2D>	MonsterThumnail;*/
};