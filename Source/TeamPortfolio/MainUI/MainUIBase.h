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

#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar* HpBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar* MpBar;

#pragma endregion 


#pragma region Public Function
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHpBar(float Percent);
	void UpdateMpBar(float Percent);

#pragma endregion 
	
};
