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

		if (InvenWidgetObject)
		{
			InvenWidgetObject->AddToViewport();
			InvenWidgetObject->SetVisibility(ESlateVisibility::Collapsed);
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
	if (InvenWidgetObject)
	{
		if (bIsToggle == false)
		{
			//InvenWidgetObject->AddToViewport();
			InvenWidgetObject->SetVisibility(ESlateVisibility::Visible);
			bIsToggle = true;
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			//SetInputMode(FInputModeUIOnly());
		}
		else
		{
			UnToggle_InvenWidget();
		}		
	}
}

void ATestUI_PC::UnToggle_InvenWidget()
{	
	InvenWidgetObject->SetVisibility(ESlateVisibility::Collapsed);//->RemoveFromViewport();
	bIsToggle = false;
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}
