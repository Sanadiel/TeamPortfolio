// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterLobby_GM.h"
#include "../MainUI/UI_PC.h"
#include "../Item/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "../MainUI/UI_PC.h"
#include "Kismet/KismetSystemLibrary.h"

void AMasterLobby_GM::StartStage()
{
	GetWorld()->ServerTravel(TEXT("Snow_Level"));
}

void AMasterLobby_GM::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMasterLobby_GM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AUI_PC* PC = Cast<AUI_PC>(NewPlayer);
	PC->AddReadyWidget();
}

void AMasterLobby_GM::Setting()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUI_PC::StaticClass(), Buttons);

	FLatentActionInfo Info;
	Info.CallbackTarget = this;
	Info.ExecutionFunction = TEXT("StartCheck");
	Info.UUID = 123;
	Info.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 5.f, Info);
}

void AMasterLobby_GM::StartCheck()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUI_PC::StaticClass(), OutActors);

	for (int Index = 0; Index != OutActors.Num(); ++Index)
	{
		PC_Array.Add(Cast<AUI_PC>(OutActors[Index]));
	}

	GetWorldTimerManager().SetTimer(
		ButtonTimer, this,
		&AMasterLobby_GM::Check,
		1.0f, true, 1.0f
	);
}

void AMasterLobby_GM::Check()
{
	if (PC_Array.Num() == 2)
	{
		if (PC_Array[0]->IsReady && PC_Array[1]->IsReady)
		{
			StartStage();
		}
	}
	else if (PC_Array.Num() == 1)
	{
		if (PC_Array[0]->IsReady)
		{
			StartStage();
		}
	}
	else
	{

	}
}
