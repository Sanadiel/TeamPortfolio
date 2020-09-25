// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_PC.h"
#include "Lobby_WidgetBase.h"

void ALobby_PC::BeginPlay()
{
	Super::BeginPlay();

	if (LobbyWidgetClass && IsLocalController())
	{
		LobbyWidgetObject = CreateWidget<ULobby_WidgetBase>(this, LobbyWidgetClass);
		LobbyWidgetObject->AddToViewport();

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}