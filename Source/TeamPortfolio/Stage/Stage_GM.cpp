// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_GM.h"
#include "../Lobby/Lobby_PC.h"
#include "../TeamP_Basic/TeamP_BasicPC.h"
#include "../Instance/TotalLog_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../TeamP_Basic/TeamP_BasicPC.h"
#include "../Boss/BossCharacter.h"
#include "../MainUI/UI_PC.h"
AStage_GM::AStage_GM()
{

}

void AStage_GM::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	ALobby_PC* Oldman = Cast<ALobby_PC>(OldPC);
	ATeamP_BasicPC* NewGuy = Cast<ATeamP_BasicPC>(NewPC);
	NewGuy->IsDefencePlayer = Oldman->IsDefencePlayer;

	//UE_LOG(LogClass, Warning, TEXT("%d"), NewGuy->IsDefencePlayer);

	Super::SwapPlayerControllers(OldPC, NewPC);
}

void AStage_GM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AUI_PC* PC = Cast<AUI_PC>(NewPlayer);

	//UE_LOG(LogClass, Warning, TEXT("PostLogin : %d"), PC->IsDefencePlayer);

	if (PC)
	{
		PC->SettingisDefence();		

		if (HasAuthority())
		{
			if (PC->IsDefencePlayer == false)
			{
				ABossCharacter* BossCharacter = GetWorld()->SpawnActor<ABossCharacter>(Boss, PC->GetPawn()->GetTransform());
				APawn* pawn = PC->GetPawn();
				PC->UnPossess();
				PC->Possess(BossCharacter);
				pawn->Destroy();
			}
		}
	}

}

void AStage_GM::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATeamP_BasicPC::StaticClass(), OutActors);

	UE_LOG(LogClass, Warning, TEXT("Begin"));	

	/*for (int i = 0; i != OutActors.Num(); ++i)
	{
		ATeamP_BasicPC* PC = Cast<ATeamP_BasicPC>(OutActors[i]);
		
		if (HasAuthority())
		{
			if (PC->IsDefencePlayer == false)
			{
				ABossCharacter* BossCharacter = GetWorld()->SpawnActor<ABossCharacter>(Boss, PC->GetPawn()->GetTransform());
				APawn* pawn = PC->GetPawn();
				PC->UnPossess();
				PC->Possess(BossCharacter);
				pawn->Destroy();
			}
		}
	}*/
}
