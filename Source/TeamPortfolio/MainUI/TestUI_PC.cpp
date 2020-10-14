// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI_PC.h"
#include "ResultFadeOutBase.h"
#include "MainUIBase.h"
#include "InventoryWidgetBase.h"
#include "../Item/Inventory.h"
#include "InventoryWidgetBase.h"
#include "EquipmentBase.h"

ATestUI_PC::ATestUI_PC()
{
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

void ATestUI_PC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);
		MainWidgetObject = CreateWidget<UMainUIBase>(this, MainWidgetClass);

		if (MainWidgetObject)
		{
			MainWidgetObject->AddToViewport();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
			MainWidgetObject->Inventory->SetMainUIParent(MainWidgetObject);
			MainWidgetObject->Inventory->SetSlotsParent();
			MainWidgetObject->Inventory->UpdateInventory(Inventory->Inven);
			MainWidgetObject->EquipWindow->SetMainUIParent(MainWidgetObject);
			MainWidgetObject->EquipWindow->SetSlotsParent();
			MainWidgetObject->EquipWindow->UpdateEquipment(Inventory->Equipment);
		}
	}
}

void ATestUI_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("InvenToggle"), IE_Pressed, this, &ATestUI_PC::Toggle_InvenWidget);
	InputComponent->BindAction(TEXT("EquipToggle"), IE_Pressed, this, &ATestUI_PC::Toggle_EquipWidget);
}

void ATestUI_PC::AddResultWidget()
{
	if (ResultWidgetObject)
	{
		ResultWidgetObject->AddToViewport();
	}
}

void ATestUI_PC::Toggle_InvenWidget()
{	
	if (bInvenToggle == false)
	{
		MainWidgetObject->ToggleInventory(true);
		bInvenToggle = true;
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		UnToggle_InvenWidget();
	}	
}

void ATestUI_PC::UnToggle_InvenWidget()
{
	MainWidgetObject->ToggleInventory(false);
	bInvenToggle = false;
	

	if (bInvenToggle == false && bEquipToggle == false)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void ATestUI_PC::Toggle_EquipWidget()
{
	if (bEquipToggle == false)
	{
		MainWidgetObject->ToggleEquipWindow(true);
		bEquipToggle = true;
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		UnToggle_EquipWidget();
	}
}

void ATestUI_PC::UnToggle_EquipWidget()
{
	MainWidgetObject->ToggleEquipWindow(false);
	bEquipToggle = false;

	if (bInvenToggle == false && bEquipToggle == false)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}