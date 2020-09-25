// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIBase.h"
#include "Components/ProgressBar.h"

void UMainUIBase::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	MpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MpBar")));
}


void UMainUIBase::UpdateHpBar(float Percent)
{
	if (HpBar)
	{
		HpBar->SetPercent(Percent);
	}
}

void UMainUIBase::UpdateMpBar(float Percent)
{
	if (MpBar)
	{
		MpBar->SetPercent(Percent);
	}
}