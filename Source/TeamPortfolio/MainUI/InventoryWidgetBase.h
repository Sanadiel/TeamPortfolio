// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UItemSlotBase> ItemSlotClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInvalidationBox* InvalidationBox;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBorder* Drag;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* Exit;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UCanvasPanel* InventoryWindow;	

#pragma endregion

#pragma region Public Function
public:
	virtual void NativeConstruct() override;
	void UpdateInventory(TArray<class AMasterItem*> Inventory);
	int GetEmptySlot();
	void SetSlot(int Index, class AMasterItem* Item);

	UFUNCTION()
	void OnExitButton();

	virtual void NativeOnInitialized() override;
#pragma endregion
};
