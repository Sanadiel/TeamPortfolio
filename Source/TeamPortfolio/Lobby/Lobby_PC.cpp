// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_PC.h"
#include "Lobby_WidgetBase.h"
#include "../Instance/TotalLog_GameInstance.h"

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

void ALobby_PC::S2C_SetGIbool_Implementation(bool bValue)
{
	//if (IsLocalPlayerController())
	//{
		UTotalLog_GameInstance* GI = GetGameInstance<UTotalLog_GameInstance>();
		if (GI)
		{
			UE_LOG(LogClass, Warning, TEXT("before : %d"), GI->isDefencePlayer);
			GI->isDefencePlayer = bValue;
			UE_LOG(LogClass, Warning, TEXT("after : %d"), GI->isDefencePlayer);
		}		
	//}
}
