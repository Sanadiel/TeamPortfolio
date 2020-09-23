// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_PC.h"

void ALobby_PC::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
}