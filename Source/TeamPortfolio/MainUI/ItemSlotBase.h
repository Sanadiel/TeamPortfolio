// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UItemSlotBase : public UUserWidget
{
	GENERATED_BODY()

#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBorder* ItemThumnail;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* ItemName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* ItemCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* ItemButton;

	class AMasterItem* SelectedItem;

	bool bUse = false;

#pragma endregion

#pragma region Public Function
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemButton();

	void UpdateItemSlot(class AMasterItem* Item);

#pragma endregion

};
