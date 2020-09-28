// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI_PC.h"
#include "ResultFadeOutBase.h"
#include "MainUIBase.h"

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

void ATestUI_PC::AddResultWidget()
{
	if (ResultWidgetObject)
	{
		ResultWidgetObject->AddToViewport();
	}
}
