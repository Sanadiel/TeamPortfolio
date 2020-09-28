// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI_PC.h"
#include "ResultFadeOutBase.h"
#include "MainUIBase.h"
#include "InventoryWidgetBase.h"

void ATestUI_PC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);
		MainWidgetObject = CreateWidget<UMainUIBase>(this, MainWidgetClass);
		InvenWidgetObject = CreateWidget<UInventoryWidgetBase>(this, InvenWidgetClass);

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
	if (InvenWidgetObject)
	{
		InvenWidgetObject->AddToViewport();
	}
}

void ATestUI_PC::UnToggle_InvenWidget()
{
	if (InvenWidgetObject)
	{
		InvenWidgetObject->RemoveFromViewport();
	}
}
