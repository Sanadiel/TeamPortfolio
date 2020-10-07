// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotBase.h"
#include "Components/Button.h"
#include "ItemWidgetBase.h"
#include "InventoryWidgetBase.h"

void UItemSlotBase::NativeConstruct()
{
	Super::NativeConstruct();
		
	ItemWidget = Cast<UItemWidgetBase>(GetWidgetFromName(TEXT("ItemWidget")));	
}

void UItemSlotBase::UpdateItemSlot(AMasterItem* Item)
{
	if (Item)
	{
		ItemWidget->UpdateItemSlot(Item);
	}
}

void UItemSlotBase::SetInvenParent(UInventoryWidgetBase * InvenParent)
{
	InvenWidget = InvenParent;
}

void UItemSlotBase::SetEquipParent(UInventoryWidgetBase* InvenParent)
{
	
}

