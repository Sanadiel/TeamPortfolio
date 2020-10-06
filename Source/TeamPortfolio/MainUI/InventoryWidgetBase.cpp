// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "Components/WrapBox.h"
#include "Components/InvalidationBox.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "ItemSlotBase.h"
#include "TestUI_PC.h"
#include "../Item/Inventory.h"

void UInventoryWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ItemSlots = Cast<UWrapBox>(GetWidgetFromName(TEXT("WrapBox_Item")));	
	Drag = Cast<UBorder>(GetWidgetFromName(TEXT("Drag")));
	Exit = Cast<UButton>(GetWidgetFromName(TEXT("Exit")));
	InventoryWindow = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("InventoryWindow")));

	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &UInventoryWidgetBase::OnExitButton);
	}
}

void UInventoryWidgetBase::UpdateInventory(TArray<class AMasterItem*> Inventory)
{
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		int FindIndex = GetEmptySlot();
		if (FindIndex > -1)
		{
			SetSlot(FindIndex, Inventory[i]);
		}
	}
}

void UInventoryWidgetBase::UpdateInventoryWithIndex(TArray<class AMasterItem*> Inventory, int32 FirstIndex)
{
	SetSlot(FirstIndex, Inventory[FirstIndex]);
}

int UInventoryWidgetBase::GetEmptySlot()
{
	for (int i = 0; i < ItemSlots->GetChildrenCount(); ++i)
	{
		UItemSlotBase* InventorySlot = Cast<UItemSlotBase>(ItemSlots->GetChildAt(i));
		if (InventorySlot && InventorySlot->bUse == false)
		{
			return i;
		}
	}

	return -1; //full
}

void UInventoryWidgetBase::SetSlot(int Index, AMasterItem* Item)
{
	UItemSlotBase* EmptySlot = Cast<UItemSlotBase>(ItemSlots->GetChildAt(Index));
	if (EmptySlot && EmptySlot->bUse == false)
	{
		EmptySlot->UpdateItemSlot(Item);
		EmptySlot->bUse = true;
		EmptySlot->SetVisibility(ESlateVisibility::Visible);
	}
}

FItemDataTable UInventoryWidgetBase::GetItemData(int32 Index)
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	return PC->Inventory->GetItemData(Index);
}

void UInventoryWidgetBase::SwapSlot(int32 FrontslotIndex, int32 OtherSlotIndex)
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	PC->Inventory->SwapSlot(FrontslotIndex, OtherSlotIndex);
	UpdateInventory(PC->Inventory->Inven);
}

void UInventoryWidgetBase::OnExitButton()
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	PC->UnToggle_InvenWidget();
}