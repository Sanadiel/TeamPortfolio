// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_ReadyWidget.h"
#include "Components/Button.h"

void ULobby_ReadyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UnReadyButton = Cast<UButton>(GetWidgetFromName(TEXT("UnReadyButton")));
	ReadyButton = Cast<UButton>(GetWidgetFromName(TEXT("ReadyButton")));
}
