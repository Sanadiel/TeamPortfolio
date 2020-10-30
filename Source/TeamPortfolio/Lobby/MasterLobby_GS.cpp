// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterLobby_GS.h"
#include "Net/UnrealNetwork.h"

AMasterLobby_GS::AMasterLobby_GS()
{
}

void AMasterLobby_GS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMasterLobby_GS, ReadyButton);
}
