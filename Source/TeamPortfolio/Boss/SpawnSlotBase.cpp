// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSlotBase.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "BossCharacter.h"
#include "MonsterSpawnProjectile.h"
#include "BossObject.h"
void USpawnSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	ImageBorder = Cast<UBorder>(GetWidgetFromName(TEXT("ImageBorder")));

	CooldownBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CooldownBar")));

	SelectButton = Cast<UButton>(GetWidgetFromName(TEXT("SelectButton")));

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &USpawnSlotBase::OnButtonClicked);
	}


	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		//Get BossPlayer so Can Access to SpawnClass.
		ABossCharacter* boss = Cast<ABossCharacter>(pc->GetPawn());
		if (boss)
		{
			int32 index = GetSlotNumber();
			if (index < boss->SpawnClasses.Num())
			{
				//Access To CDO and get the Info.
				FMonsterSpawnInfo monsterSpawnInfo = boss->SpawnClasses[index]->GetDefaultObject<AMonsterSpawnProjectile>()->MonsterSpawnInfo;

				//set UMG Icon.
				if (monsterSpawnInfo.Thumbnail)
				{
					ImageBorder->SetBrushFromTexture(monsterSpawnInfo.Thumbnail);
				}
			}
		}
	}


}

void USpawnSlotBase::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	//UE_LOG(LogClass, Warning, TEXT("UserWidgetTick"));

	UpdateCooldown();
}

void USpawnSlotBase::OnButtonClicked()
{
	UE_LOG(LogClass, Warning, TEXT("%s's button Clicked."), *GetName());

	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		//Get BossPlayer so Can Access to SpawnClass.
		ABossCharacter* boss = Cast<ABossCharacter>(pc->GetPawn());
		if (boss)
		{

			int32 index = GetSlotNumber();
			//UE_LOG(LogClass, Warning, TEXT("%s"),*number);
			if (index < boss->SpawnClasses.Num() && boss->SpawnClasses[index])
			{
				if (boss->GetGrabbedComponent())
				{
					UE_LOG(LogClass, Warning, TEXT("Projectile Spawn Failed. You Already Hold Something."));
					return;
				}

				if (boss->SpawnCooldown[index] < boss->MaxSpawnCooldown[index])
				{
					UE_LOG(LogClass, Warning, TEXT("Projectile Spawn Failed. Waiting for the Cooldown"));
					return;
				}

				//boss->SetProjectileClass(boss->SpawnClasses[index]);
				FTransform transform;
				transform.SetLocation(boss->HoldPosition->GetComponentLocation());
				FActorSpawnParameters params;
				params.Owner = boss;
				
				AMonsterSpawnProjectile* projectile = GetWorld()->SpawnActor<AMonsterSpawnProjectile>(boss->SpawnClasses[index],transform,params);
				if (projectile)
				{
					boss->HoldSpawnProjectile(projectile);
					boss->SpawnCooldown[index] = 0.0f;
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("Projectile Spawn Failed"));
				}
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("Invalid. you are trying to access %d. Current Spawn Class Size is %d"), index, boss->SpawnClasses.Num());
			}

		}
	}

}

void USpawnSlotBase::UpdateCooldown()
{

	//Update Cooldown In Slot ProgressBar
	APlayerController* pc = GetOwningPlayer();
	if (pc && pc->IsLocalPlayerController())
	{
		ABossCharacter* boss = Cast<ABossCharacter>(pc->GetPawn());
		if (boss)
		{
			int32 index = GetSlotNumber();
			if (index < boss->SpawnCooldown.Num() && CooldownBar)
			{
				float currentCooldown = boss->SpawnCooldown[index];
				CooldownBar->SetPercent(currentCooldown / boss->MaxSpawnCooldown[index]);
			}
		}
	}
}

int32 USpawnSlotBase::GetSlotNumber() const
{
	//Get Number. ex) "SpawnSlot7" == 7
	FString widgetName = GetName();
	widgetName.RemoveFromStart(TEXT("SpawnSlot"));
	FString number = widgetName;
	return FCString::Atoi(*number);
}
