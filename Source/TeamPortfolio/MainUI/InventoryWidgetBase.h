// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TeamPortfolio.h"
#include "../Item/ItemDataTable.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UWrapBox* ItemSlots;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBorder* Drag;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* Exit;

#pragma endregion

#pragma region Public Function
public:
	virtual void NativeConstruct() override;
	void UpdateInventory(TArray<class AMasterItem*> Inventory);
	void UpdateInventoryWithIndex(TArray<class AMasterItem*> Inventory, int32 FirstIndex);
	int GetEmptySlot();
	void SetSlot(int Index, class AMasterItem* Item);
	void SetSlotsParent();

	FItemDataTable GetItemData(int32 Index);

	UFUNCTION(BlueprintCallable)
	void SwapSlot(int32 FrontslotIndex, int32 OtherSlotIndex);

	UFUNCTION()
	void OnExitButton();

#pragma endregion
};
