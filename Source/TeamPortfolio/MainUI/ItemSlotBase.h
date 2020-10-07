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
	class UItemWidgetBase* ItemWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInventoryWidgetBase* InvenWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotIndex;

#pragma endregion

#pragma region Public Function
public:
	virtual void NativeConstruct() override;
	void UpdateItemSlot(class AMasterItem* Item);
	void SetInvenParent(class UInventoryWidgetBase* InvenParent);
	void SetEquipParent(class UInventoryWidgetBase* InvenParent);

#pragma endregion

};
