// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHPWidgetBase.h"
#include "Components/Progressbar.h"

void UMonsterHPWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	HPbar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterHpBarUI")));
}

void UMonsterHPWidgetBase::HpBarUpdate(float Percent)
{
	HPbar->SetPercent(Percent);
	//MonsterHpBarUI
}
