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
	class UHpBarBase* HpBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar* MpBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInventoryWidgetBase* Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStatHoverBase* Hover;
	

#pragma endregion 


#pragma region Public Function
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHpBar(float Percent);
	UFUNCTION(BlueprintCallable)
	void UpdateMpBar(float Percent);

	void ToggleInventory(bool bValue);	

	UFUNCTION()
	void ToggleHover(FVector2D Position, bool bValue);

#pragma endregion 
	
};
