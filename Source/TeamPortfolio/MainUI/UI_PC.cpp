// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_PC.h"
#include "ResultFadeOutBase.h"
#include "MainUIBase.h"
#include "InventoryWidgetBase.h"
#include "../Item/Inventory.h"
#include "InventoryWidgetBase.h"
#include "EquipmentBase.h"
#include "../Instance/TotalLog_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "../Stage/Stage_GM.h"
#include "../Boss/BossCharacter.h"
#include "../Lobby/Lobby_WidgetBase.h"
#include "../Base/Base_GM.h"
#include "../Lobby/Lobby_ReadyWidget.h"

AUI_PC::AUI_PC()
{
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

void AUI_PC::BeginPlay()
{
	Super::BeginPlay();

	SettingUI();
}

void AUI_PC::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(TEXT("InvenToggle"), IE_Pressed, this, &AUI_PC::Toggle_InvenWidget);
	InputComponent->BindAction(TEXT("EquipToggle"), IE_Pressed, this, &AUI_PC::Toggle_EquipWidget);
}

void AUI_PC::Destroyed()
{
	if (IsValid(MainWidgetObject))
	{
		MainWidgetObject->RemoveFromParent();
	}

	if (IsValid(ResultWidgetObject))
	{
		ResultWidgetObject->RemoveFromParent();
	}

	if (IsValid(LobbyWidgetObject))
	{
		LobbyWidgetObject->RemoveFromParent();
	}

	UTotalLog_GameInstance* GI = GetGameInstance<UTotalLog_GameInstance>();
	if (IsValid(GI))
	{
		GI->Inven = Inventory->Inven;
		GI->Equip = Inventory->Equipment;
	}

	Super::Destroyed();
}

UMainUIBase* AUI_PC::GetMainUI()
{
	return MainWidgetObject;
}

void AUI_PC::SettingUI()
{
	if (UITestMode == true)
	{
		UE_LOG(LogClass, Warning, TEXT("-----------PC is Test Mode-----------"))
		return;
	}		

	if (IsLocalPlayerController())
	{
		UTotalLog_GameInstance* GI = GetGameInstance<UTotalLog_GameInstance>();
		ABase_GM* GM = Cast<ABase_GM>(UGameplayStatics::GetGameMode(GetWorld()));

		if (IsValid(GI))
		{
			IsDefencePlayer = GI->isDefencePlayer;
		}

		if (IsDefencePlayer == true)
		{			
			MainWidgetObject = CreateWidget<UMainUIBase>(this, MainWidgetClass);
			Tags.Add(TEXT("Defence"));

			if (MainWidgetObject)
			{
				if (GI->Inven.Num() == 0)
				{
					Inventory->DataLoading();
				}
				else
				{
					Inventory->PassData(GI->Inven, GI->Equip);
				}				

				MainWidgetObject->AddToViewport();
				bShowMouseCursor = false;
				SetInputMode(FInputModeGameOnly());
				MainWidgetObject->Inventory->SetMainUIParent(MainWidgetObject);
				MainWidgetObject->Inventory->SetSlotsParent();
				MainWidgetObject->Inventory->UpdateInventory(Inventory->Inven);
				MainWidgetObject->EquipWindow->SetMainUIParent(MainWidgetObject);
				MainWidgetObject->EquipWindow->SetSlotsParent();
				MainWidgetObject->EquipWindow->UpdateEquipment(Inventory->Equipment);
			}
		}
		else
		{
			C2S_SpawnandPossess();
			Tags.Add(TEXT("Offence"));
		}

		C2S_ReplaceWorld(Tags[0]);
		SettingReadyWidget();
	}
}

void AUI_PC::SettingUI_TEST()
{
	IsDefencePlayer = true;

	//ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);
	MainWidgetObject = CreateWidget<UMainUIBase>(this, MainWidgetClass);
	Tags.Add(TEXT("Defence"));

	if (MainWidgetObject)
	{
		Inventory->DataLoading();

		MainWidgetObject->AddToViewport();
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		MainWidgetObject->Inventory->SetMainUIParent(MainWidgetObject);
		MainWidgetObject->Inventory->SetSlotsParent();
		MainWidgetObject->Inventory->UpdateInventory(Inventory->Inven);
		MainWidgetObject->EquipWindow->SetMainUIParent(MainWidgetObject);
		MainWidgetObject->EquipWindow->SetSlotsParent();
		MainWidgetObject->EquipWindow->UpdateEquipment(Inventory->Equipment);
	}
}

void AUI_PC::AddResultWidget()
{
	if (IsValid(ResultWidgetObject))
		return;

	ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);

	if (ResultWidgetObject)
	{
		ResultWidgetObject->AddToViewport();
	}
}

void AUI_PC::AddTimeWidget()
{
	LobbyWidgetObject = CreateWidget<ULobby_WidgetBase>(this, LobbyWidgetClass);

	if (LobbyWidgetObject)
	{
		LobbyWidgetObject->AddToViewport();
	}
}

void AUI_PC::AddReadyWidget_Implementation()
{
	IsMasterLobby = true;
}

void AUI_PC::SettingReadyWidget()
{
	if (IsMasterLobby == true)
	{
		if (IsDefencePlayer == false)
		{
			ReadyWidgetObject = CreateWidget<ULobby_ReadyWidget>(this, ReadyWidgetClass);

			if (ReadyWidgetObject)
			{
				ReadyWidgetObject->AddToViewport();
			}
		}
		else
		{
			GetMainUI()->ReadyWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AUI_PC::Toggle_InvenWidget()
{	
	if (IsDefencePlayer == true)
	{
		if (bInvenToggle == false)
		{
			MainWidgetObject->ToggleInventory(true);
			bInvenToggle = true;
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
		}
		else
		{
			UnToggle_InvenWidget();
		}
	}	
}

void AUI_PC::UnToggle_InvenWidget()
{
	MainWidgetObject->ToggleInventory(false);
	bInvenToggle = false;

	if (bInvenToggle == false && bEquipToggle == false)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void AUI_PC::Toggle_EquipWidget()
{
	if (IsDefencePlayer == true)
	{
		if (bEquipToggle == false)
		{
			MainWidgetObject->ToggleEquipWindow(true);
			bEquipToggle = true;
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
		}
		else
		{
			UnToggle_EquipWidget();
		}
	}	
}

void AUI_PC::UnToggle_EquipWidget()
{
	MainWidgetObject->ToggleEquipWindow(false);
	bEquipToggle = false;

	if (bInvenToggle == false && bEquipToggle == false)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void AUI_PC::S2C_SettingisDefence_Implementation()
{
	UTotalLog_GameInstance* GI = GetGameInstance<UTotalLog_GameInstance>();

	if (IsLocalPlayerController())
	{
		if (GI)
		{
			UE_LOG(LogClass, Warning, TEXT("Currrent GI Bool : %d"), GI->isDefencePlayer);
			IsDefencePlayer = GI->isDefencePlayer;
		}
	}	
}

void AUI_PC::C2S_SpawnandPossess_Implementation()
{
	ABossCharacter* BossCharacter = GetWorld()->SpawnActor<ABossCharacter>(Boss, StartSpot->GetTransform());
	APawn* pawn = GetPawn();
	UnPossess();
	Possess(BossCharacter);
	BossCharacter->CreateUI();
	pawn->SetActorHiddenInGame(true);
	pawn->Destroy();
}

void AUI_PC::C2S_ReplaceWorld_Implementation(FName Tag)
{
	ABase_GM* GM = Cast<ABase_GM>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(GM))
	{
		GM->Replace_Player(this, Tag);
	}
}

void AUI_PC::C2S_SetIsReady_Implementation(bool bValue)
{
	IsReady = bValue;
}

void AUI_PC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUI_PC, IsDefencePlayer);
	DOREPLIFETIME(AUI_PC, IsReady);
}