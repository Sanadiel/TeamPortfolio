// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopBase.h"
#include "TestUI_PC.h"
#include "Components/Button.h"

void UShopBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShopBase::OnExitButtonShop()
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	PC->UnToggle_InvenWidget();
	SetVisibility(ESlateVisibility::Collapsed);
}

void UShopBase::SetExitButton()
{
	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &UShopBase::OnExitButtonShop);
	}
}