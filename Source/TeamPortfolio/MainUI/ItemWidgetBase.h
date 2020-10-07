// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UItemWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBorder* ItemThumnail;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* ItemCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bUse = false;

	class AMasterItem* Item;

#pragma endregion

#pragma region Public Function
public:
	virtual void NativeConstruct() override;

	void UpdateItemSlot(class AMasterItem* ParamItem);

#pragma endregion
};
