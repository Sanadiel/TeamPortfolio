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

	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		ABossCharacter* boss = Cast<ABossCharacter>(pc->GetPawn());
		if (boss)
		{
			int32 index = GetSlotNumber();
			if (index < boss->SpawnCooldown.Num() && CooldownBar)
			{
				float cooldown = boss->SpawnCooldown[index];
				CooldownBar->SetPercent(cooldown / 10.0f);
			}
		}
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

			int32 index = GetSlotNumber();
			//UE_LOG(LogClass, Warning, TEXT("%s"),*number);
			if (index < boss->SpawnClasses.Num() && boss->SpawnClasses[index])
			{
				//boss->SetProjectileClass(boss->SpawnClasses[index]);
				FTransform transform;
				transform.SetLocation(boss->HoldPosition->GetComponentLocation());
				AMonsterSpawnProjectile* projectile = GetWorld()->SpawnActor<AMonsterSpawnProjectile>(boss->SpawnClasses[index],transform);
				if (projectile)
				{
					boss->HoldSpawnProjectile(projectile);
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

int32 USpawnSlotBase::GetSlotNumber() const
{
	FString widgetName = GetName();
	widgetName.RemoveFromStart(TEXT("SpawnSlot"));
	FString number = widgetName;
	return FCString::Atoi(*number);
}
