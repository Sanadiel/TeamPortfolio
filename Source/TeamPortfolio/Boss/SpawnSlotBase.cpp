// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSlotBase.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "BossCharacter.h"
#include "MonsterSpawnProjectile.h"
void USpawnSlotBase::NativeConstruct()
{
	ImageBorder = Cast<UBorder>(GetWidgetFromName(TEXT("ImageBorder")));

	CooldownBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CooldownBar")));

	SelectButton = Cast<UButton>(GetWidgetFromName(TEXT("SelectButton")));

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &USpawnSlotBase::OnButtonClicked);
	}
}

void USpawnSlotBase::OnButtonClicked()
{
	//UE_LOG(LogClass, Warning, TEXT("%s's button Clicked."), *GetName());

	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		//Get BossPlayer so Can Access to SpawnClass.
		ABossCharacter* boss = Cast<ABossCharacter>(pc->GetPawn());
		if (boss)
		{
			FString widgetName = GetName();
			widgetName.RemoveFromStart(TEXT("SpawnSlot"));
			FString number = widgetName;
			int32 index = FCString::Atoi(*number);
			//UE_LOG(LogClass, Warning, TEXT("%s"),*number);
			if (index < boss->SpawnClasses.Num() && boss->SpawnClasses[index])
			{
				boss->SetProjectileClass(boss->SpawnClasses[index]);
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("Invalid. you are trying to access %d. Current Spawn Class Size is %d"), index, boss->SpawnClasses.Num());
			}

		}
	}

}
