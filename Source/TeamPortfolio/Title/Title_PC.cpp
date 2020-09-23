// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_PC.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Title_UserWidgetBase.h"

void ATitle_PC::BeginPlay()
{
	Super::BeginPlay();

	if (TitleWidgetClass && IsLocalController())
	{
		TitleWidgetObject = CreateWidget<UTitle_UserWidgetBase>(this, TitleWidgetClass);
		TitleWidgetObject->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void ATitle_PC::StartServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, TEXT("listen"));
}

void ATitle_PC::ConnectServer(FString ServerIP)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*ServerIP));
}
