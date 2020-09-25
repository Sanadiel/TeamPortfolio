// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_WidgetBase.h"
#include "Components/TextBlock.h"

void ULobby_WidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	TimeLeftMessage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TimeLeftMessage")));
	TimeLeftMessage->SetVisibility(ESlateVisibility::Collapsed);
}

void ULobby_WidgetBase::SetMessage(int LeftTime)
{
	FString Temp = FString::Printf(TEXT("%d초 후에 게임이 시작됩니다."), LeftTime);
	if (TimeLeftMessage)
	{
		TimeLeftMessage->SetText(FText::FromString(Temp));
	}

	TimeLeftMessage->SetVisibility(ESlateVisibility::Visible);
}
