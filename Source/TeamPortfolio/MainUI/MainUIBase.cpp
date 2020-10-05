// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIBase.h"
#include "Components/ProgressBar.h"
#include "InventoryWidgetBase.h"
#include "StatHoverBase.h"
#include "HpBarBase.h"

void UMainUIBase::NativeConstruct()
{
	Super::NativeConstruct();

	//HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar_1")));
	HpBar = Cast<UHpBarBase>(GetWidgetFromName(TEXT("HpBar_1")));
	MpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MpBar")));
	Inventory = Cast<UInventoryWidgetBase>(GetWidgetFromName(TEXT("Inventory")));
	Hover = Cast<UStatHoverBase>(GetWidgetFromName(TEXT("Hover")));

	Inventory->SetVisibility(ESlateVisibility::Collapsed);
	HpBar->Fuc_DeleSingle_TwoParam.BindUFunction(this, FName("ToggleHover"));

	UE_LOG(LogClass, Warning, TEXT("NativeConstruct :: MainUI"));
}

void UMainUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogClass, Warning, TEXT("NativeOnInitialized :: MainUI"));
}


void UMainUIBase::UpdateHpBar(float Percent)
{
	if (HpBar)
	{
		HpBar->UpdateHpBar(Percent);
	}
}

void UMainUIBase::UpdateMpBar(float Percent)
{
	if (MpBar)
	{
		MpBar->SetPercent(Percent);
	}
}

void UMainUIBase::ToggleInventory(bool bValue)
{
	if (bValue)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Inventory->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainUIBase::ToggleHover(FVector2D Position, bool bValue)
{
	if (bValue)
	{
		Hover->SetVisibility(ESlateVisibility::Visible);
		Hover->SetPositionInViewport(Position, false);
	}
	else
	{
		Hover->SetVisibility(ESlateVisibility::Collapsed);
	}

}
