// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI_PC.h"
#include "ResultFadeOutBase.h"

void ATestUI_PC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);
		
		if (ResultWidgetObject)
		{
			ResultWidgetObject->AddToViewport();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
	}
}