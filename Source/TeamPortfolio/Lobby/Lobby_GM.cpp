// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_GM.h"
#include "Lobby_GS.h"

void ALobby_GM::StartGame()
{
	GetWorld()->ServerTravel(TEXT("UITest_Level"));
}

void ALobby_GM::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		LobbyTimer,
		this,
		&ALobby_GM::DecreaseTime,
		1.0f,
		true,
		1.0f
	);
}

void ALobby_GM::DecreaseTime()
{
	ALobby_GS* GS = GetGameState<ALobby_GS>();
	if (GS)
	{
		GS->LeftTime--;
		GS->OnRep_LeftTime();

		if (GS->LeftTime < 0)
		{
			//게임 시작
			StartGame();
		}

		UE_LOG(LogClass, Warning, TEXT("%d"), GS->LeftTime);
	}
}