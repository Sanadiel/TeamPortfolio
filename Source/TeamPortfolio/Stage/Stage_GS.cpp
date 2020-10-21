// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_GS.h"
#include "Kismet/GameplayStatics.h"
#include "../MainUI/UI_PC.h"
#include "Net/UnrealNetwork.h"
#include "../Lobby/Lobby_WidgetBase.h"


void AStage_GS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStage_GS, LeftTime);
}

void AStage_GS::OnRep_LeftTime()
{
	AUI_PC* PC = Cast<AUI_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{		
		if (!IsValid(PC->LobbyWidgetObject))
		{
			CreateTimeUI_Implementation();
		}
		else
		{
			PC->LobbyWidgetObject->SetMessage(LeftTime, false);
		}
	}
}

void AStage_GS::CreateTimeUI_Implementation()
{
	AUI_PC* PC = Cast<AUI_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->AddTimeWidget();
		PC->LobbyWidgetObject->SetMessage(LeftTime, false);
	}
}
