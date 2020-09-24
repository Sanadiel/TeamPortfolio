// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UMainUIBase : public UUserWidget
{
	GENERATED_BODY()

#pragma region Public Function
public:
	virtual void NativeConstruct() override;

#pragma endregion 
	
};
