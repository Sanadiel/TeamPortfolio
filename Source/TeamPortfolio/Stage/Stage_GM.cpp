// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_GM.h"
#include "../Lobby/Lobby_PC.h"
#include "../TeamP_Basic/TeamP_BasicPC.h"
#include "../Instance/TotalLog_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../TeamP_Basic/TeamP_BasicPC.h"
#include "../Boss/BossCharacter.h"
#include "../MainUI/UI_PC.h"
#include "Stage_GS.h"

AStage_GM::AStage_GM()
{

}

//void AStage_GM::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
//{
//	ALobby_PC* Oldman = Cast<ALobby_PC>(OldPC);
//	ATeamP_BasicPC* NewGuy = Cast<ATeamP_BasicPC>(NewPC);
//	NewGuy->IsDefencePlayer = Oldman->IsDefencePlayer;
//
//	Super::SwapPlayerControllers(OldPC, NewPC);
//}

void AStage_GM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AUI_PC* PC = Cast<AUI_PC>(NewPlayer);

	if (IsValid(PC))
	{
		PC->S2C_SettingisDefence();
	}
}

void AStage_GM::BeginPlay()
{
	Super::BeginPlay();

	StartCountDown();
}

void AStage_GM::StartCountDown()
{
	GetWorldTimerManager().SetTimer(
		GameTimer,
		this,
		&AStage_GM::DecreaseTime,
		1.0f,
		true,
		1.0f
	);
}

void AStage_GM::DecreaseTime()
{
	AStage_GS* GS = GetGameState<AStage_GS>();
	if (GS)
	{
		GS->LeftTime--;
		GS->OnRep_LeftTime();

		if (GS->LeftTime <= 0)
		{
			//게임 시작
			GetWorldTimerManager().ClearTimer(GameTimer);
			Travel_MasterLobby();
		}
	}
}

void AStage_GM::Travel_MasterLobby()
{
	GetWorld()->ServerTravel(TEXT("MasterLobby"));
}

//APawn * AStage_GM::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
//{
//	Super::SpawnDefaultPawnFor(NewPlayer, StartSpot);
//
//	ABossCharacter* BossCharacter = GetWorld()->SpawnActor<ABossCharacter>(Boss, StartSpot->GetTransform());
//	APawn* pawn = NewPlayer->GetPawn();
//	NewPlayer->UnPossess();
//	NewPlayer->Possess(BossCharacter);
//	pawn->Destroy();
//
//	return nullptr;
//}

AActor* AStage_GM::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart(Player);
}

AActor * AStage_GM::FindPlayerStart_Implementation(AController* Player, const FString & IncomingName)
{
	return Super::FindPlayerStart(Player, IncomingName);
}
