// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_UserWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Title_PC.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CanvasPanel.h"


void UTitle_UserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ServerIP = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIP")));
	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectButton")));
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	SinglePlayButton = Cast<UButton>(GetWidgetFromName(TEXT("SinglePlayButton")));
	MultiPlayButton = Cast<UButton>(GetWidgetFromName(TEXT("MultiPlayButton")));
	OptionButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	MultiWindow = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("MultiWindow")));

	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UTitle_UserWidgetBase::OnConnectButton);
	}

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTitle_UserWidgetBase::OnStartButton);
	}

	if (SinglePlayButton)
	{
		SinglePlayButton->OnClicked.AddDynamic(this, &UTitle_UserWidgetBase::OnSinglePlayButton);
	}

	if (MultiPlayButton)
	{
		MultiPlayButton->OnClicked.AddDynamic(this, &UTitle_UserWidgetBase::OnMultiPlayButton);
	}

	if (OptionButton)
	{
		OptionButton->OnClicked.AddDynamic(this, &UTitle_UserWidgetBase::OnOptionButton);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UTitle_UserWidgetBase::OnExitButton);
	}

	MultiWindow->SetVisibility(ESlateVisibility::Collapsed);
}

void UTitle_UserWidgetBase::OnConnectButton()
{
	ATitle_PC* PC = GetOwningPlayer<ATitle_PC>();
	if (PC)
	{
		if (ServerIP)
		{
			FString ServerIPAddress = ServerIP->GetText().ToString();

			PC->ConnectServer(ServerIPAddress);
		}
	}
}

void UTitle_UserWidgetBase::OnStartButton()
{
	ATitle_PC* PC = GetOwningPlayer<ATitle_PC>();
	if (PC)
	{
		PC->StartServer();
	}
}

void UTitle_UserWidgetBase::OnSinglePlayButton()
{

}

void UTitle_UserWidgetBase::OnMultiPlayButton()
{
	MultiWindow->SetVisibility(ESlateVisibility::Visible);
}

void UTitle_UserWidgetBase::OnOptionButton()
{

}

void UTitle_UserWidgetBase::OnExitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true); 
}

void UTitle_UserWidgetBase::SaveUserID()
{
	//ATitle_PC* PC = GetOwningPlayer<ATitle_PC>();
}