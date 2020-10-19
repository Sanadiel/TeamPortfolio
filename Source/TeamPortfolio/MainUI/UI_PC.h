// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI_PC.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API AUI_PC : public APlayerController
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
	bool bInvenToggle = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	bool bEquipToggle = false;

#pragma endregion

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inven")
	class UInventory* Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Player")
	bool IsDefencePlayer = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	bool UITestMode = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Boss")
	TSubclassOf<class ABossCharacter> Boss;
#pragma endregion


#pragma region Public Function
public:
	AUI_PC();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	class UMainUIBase* GetMainUI();

	void SettingUI();

	UFUNCTION(BlueprintCallable)
	void SettingUI_TEST();

	void AddResultWidget();

	void Toggle_InvenWidget();
	void UnToggle_InvenWidget();

	void Toggle_EquipWidget();
	void UnToggle_EquipWidget();

	UFUNCTION(Client , Reliable)
	void S2C_SettingisDefence();
	void S2C_SettingisDefence_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_SpawnandPossess();
	void C2S_SpawnandPossess_Implementation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma endregion
};
