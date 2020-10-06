// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestUI_PC.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API ATestUI_PC : public APlayerController
{
	GENERATED_BODY()

#pragma region Public Member
#pragma region UI
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UResultFadeOutBase> ResultWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UResultFadeOutBase* ResultWidgetObject;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UMainUIBase> MainWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UMainUIBase* MainWidgetObject;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	bool bIsToggle = false;

#pragma endregion

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inven")
	class UInventory* Inventory;

#pragma endregion


#pragma region Public Function
public:
	ATestUI_PC();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void AddResultWidget();

	void Toggle_InvenWidget();
	void UnToggle_InvenWidget();

#pragma endregion
};
