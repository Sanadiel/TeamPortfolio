// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI_PC.h"
#include "ResultFadeOutBase.h"
#include "MainUIBase.h"
#include "InventoryWidgetBase.h"
#include "../Item/Inventory.h"

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
		}
	}
}

void ATestUI_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("InvenToggle"), IE_Pressed, this, &ATestUI_PC::Toggle_InvenWidget);	
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
	if (bIsToggle == false)
	{
		MainWidgetObject->ToggleInventory(true);
		bIsToggle = true;
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
	bIsToggle = false;
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}
