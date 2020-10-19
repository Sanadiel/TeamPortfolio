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

AUI_PC::AUI_PC()
{
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	//UE_LOG(LogClass, Warning, TEXT("UI_PC : Construct : %s"), *GetName());
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

		if (IsValid(GI))
		{
			IsDefencePlayer = GI->isDefencePlayer;
		}		

		if (IsDefencePlayer == true)
		{
			ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);
			MainWidgetObject = CreateWidget<UMainUIBase>(this, MainWidgetClass);

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
		else
		{
			C2S_SpawnandPossess();
		}
	}
}

void AUI_PC::SettingUI_TEST()
{
	IsDefencePlayer = true;

	ResultWidgetObject = CreateWidget<UResultFadeOutBase>(this, ResultWidgetClass);
	MainWidgetObject = CreateWidget<UMainUIBase>(this, MainWidgetClass);

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
	if (ResultWidgetObject)
	{
		ResultWidgetObject->AddToViewport();
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
	pawn->Destroy();
}

void AUI_PC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUI_PC, IsDefencePlayer);
}