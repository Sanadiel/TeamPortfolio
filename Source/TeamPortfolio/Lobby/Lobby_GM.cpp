// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_GM.h"
#include "Lobby_GS.h"
#include "Kismet/GameplayStatics.h"
#include "SelectButtonBase.h"

void ALobby_GM::StartGame()
{
	GetWorld()->ServerTravel(TEXT("UITest_Level"));
}

void ALobby_GM::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASelectButtonBase::StaticClass(), Buttons);

	StartCheckButton();
}

void ALobby_GM::StartCheckButton()
{
	GetWorldTimerManager().SetTimer(
		ButtonTimer,
		this,
		&ALobby_GM::CheckButton,
		1.0f,
		true,
		1.0f
	);
}

void ALobby_GM::CheckButton()
{
	if (Buttons.Num() == 2)
	{
		bool button0 = Cast<ASelectButtonBase>(Buttons[0])->bIsPush;
		bool button1 = Cast<ASelectButtonBase>(Buttons[1])->bIsPush;

		if (button0 && button1)
		{
			GetWorldTimerManager().ClearTimer(ButtonTimer);
			StartCountDown();
		}
	}
}

void ALobby_GM::StartCountDown()
{
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
			GetWorldTimerManager().ClearTimer(LobbyTimer);
			StartGame();
		}
	}
}